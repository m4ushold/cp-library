import os
import json
import re

# ================= 설정 =================
SRC_DIR = "./src"

# 1. VS Code용 출력 경로
VSCODE_OUTPUT = "snippets/vscode"
# =======================================

def parse_file(filepath):
    """파일을 읽어서 @snippet 태그별로 코드를 추출함"""
    with open(filepath, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    snippets = {}
    current_trigger = None
    current_code = []
    
    # 정규표현식: // @snippet 트리거명
    trigger_pattern = re.compile(r'^\s*//\s*@snippet\s+(\w+)')

    for line in lines:
        match = trigger_pattern.search(line)
        if match:
            if current_trigger:
                snippets[current_trigger] = current_code
            current_trigger = match.group(1)
            current_code = []
            continue 

        if current_trigger:
            # 주석 및 빈 줄 처리는 취향껏 (여기서는 그대로 저장)
            current_code.append(line.rstrip())

    if current_trigger:
        snippets[current_trigger] = current_code
        
    return snippets

def generate_vscode_json(all_snippets):
    """VS Code용 JSON 파일 생성"""
    vscode_snippets = {}
    for trigger, code_lines in all_snippets.items():
        vscode_snippets[trigger] = {
            "prefix": trigger,
            "body": code_lines,
            "description": f"CP Library: {trigger}"
        }
    
    os.makedirs(os.path.dirname(VSCODE_OUTPUT), exist_ok=True)
    with open(VSCODE_OUTPUT, 'w', encoding='utf-8') as f:
        json.dump(vscode_snippets, f, indent=4, ensure_ascii=False)
    print(f"✅ VS Code: Generated {len(all_snippets)} snippets -> {VSCODE_OUTPUT}")

def main():
    all_snippets = {}
    
    for root, dirs, files in os.walk(SRC_DIR):
        for file in files:
            if file.endswith((".hpp", ".cpp")):
                filepath = os.path.join(root, file)
                file_snippets = parse_file(filepath)
                
                for trigger, code in file_snippets.items():
                    all_snippets[trigger] = code

    generate_vscode_json(all_snippets)

if __name__ == "__main__":
    main()
