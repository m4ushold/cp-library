import os
import json
import re
from pathlib import Path

# ================= 설정 =================
BASE_DIR = Path(__file__).resolve().parent
SRC_DIR = BASE_DIR / "src"
VSCODE_OUTPUT = BASE_DIR / "cpp.json"
# =======================================


def parse_file(filepath):
    """파일을 읽어서 @snippet 태그별로 코드를 추출함"""
    with open(filepath, "r", encoding="utf-8") as f:
        lines = f.readlines()

    snippets = {}
    current_trigger = None
    current_code = []

    trigger_pattern = re.compile(r"^\s*//\s*@snippet\s+(\w+)")

    for line in lines:
        match = trigger_pattern.search(line)
        if match:
            if current_trigger:
                snippets[current_trigger] = current_code
            current_trigger = match.group(1)
            current_code = []
            continue
        if current_trigger:
            current_code.append(line.rstrip())

    if current_trigger:
        snippets[current_trigger] = current_code

    return snippets


def generate_vscode_json(all_snippets):
    """VS Code(LuaSnip from_vscode)용 JSON 파일 생성"""
    vscode_snippets = {
        trigger: {
            "prefix": trigger,
            "body": code_lines,
            "description": f"CP Library: {trigger}",
        }
        for trigger, code_lines in all_snippets.items()
    }

    VSCODE_OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    with open(VSCODE_OUTPUT, "w", encoding="utf-8") as f:
        json.dump(vscode_snippets, f, indent=4, ensure_ascii=False)

    print(f"Generated {len(all_snippets)} snippets -> {VSCODE_OUTPUT}")


def main():
    all_snippets = {}

    for root, _dirs, files in os.walk(SRC_DIR):
        for file in files:
            if file.endswith((".hpp", ".cpp")):
                filepath = os.path.join(root, file)
                all_snippets.update(parse_file(filepath))

    generate_vscode_json(all_snippets)


if __name__ == "__main__":
    main()
