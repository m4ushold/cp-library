---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.11.15/x64/lib/python3.11/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.11.15/x64/lib/python3.11/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 96, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "import os\nimport json\nimport re\nfrom pathlib import Path\n\n# =================\
    \ \uC124\uC815 =================\nBASE_DIR = Path(__file__).resolve().parent\n\
    SRC_DIR = BASE_DIR / \"src\"\nVSCODE_OUTPUT = BASE_DIR / \"cpp.json\"\n# =======================================\n\
    \n\ndef parse_file(filepath):\n    \"\"\"\uD30C\uC77C\uC744 \uC77D\uC5B4\uC11C\
    \ @snippet \uD0DC\uADF8\uBCC4\uB85C \uCF54\uB4DC\uB97C \uCD94\uCD9C\uD568\"\"\"\
    \n    with open(filepath, \"r\", encoding=\"utf-8\") as f:\n        lines = f.readlines()\n\
    \n    snippets = {}\n    current_trigger = None\n    current_code = []\n\n   \
    \ trigger_pattern = re.compile(r\"^\\s*//\\s*@snippet\\s+(\\w+)\")\n\n    for\
    \ line in lines:\n        match = trigger_pattern.search(line)\n        if match:\n\
    \            if current_trigger:\n                snippets[current_trigger] =\
    \ current_code\n            current_trigger = match.group(1)\n            current_code\
    \ = []\n            continue\n        if current_trigger:\n            current_code.append(line.rstrip())\n\
    \n    if current_trigger:\n        snippets[current_trigger] = current_code\n\n\
    \    return snippets\n\n\ndef generate_vscode_json(all_snippets):\n    \"\"\"\
    VS Code(LuaSnip from_vscode)\uC6A9 JSON \uD30C\uC77C \uC0DD\uC131\"\"\"\n    vscode_snippets\
    \ = {\n        trigger: {\n            \"prefix\": trigger,\n            \"body\"\
    : code_lines,\n            \"description\": f\"CP Library: {trigger}\",\n    \
    \    }\n        for trigger, code_lines in all_snippets.items()\n    }\n\n   \
    \ VSCODE_OUTPUT.parent.mkdir(parents=True, exist_ok=True)\n    with open(VSCODE_OUTPUT,\
    \ \"w\", encoding=\"utf-8\") as f:\n        json.dump(vscode_snippets, f, indent=4,\
    \ ensure_ascii=False)\n\n    print(f\"Generated {len(all_snippets)} snippets ->\
    \ {VSCODE_OUTPUT}\")\n\n\ndef main():\n    all_snippets = {}\n\n    for root,\
    \ _dirs, files in os.walk(SRC_DIR):\n        for file in files:\n            if\
    \ file.endswith((\".hpp\", \".cpp\")):\n                filepath = os.path.join(root,\
    \ file)\n                all_snippets.update(parse_file(filepath))\n\n    generate_vscode_json(all_snippets)\n\
    \n\nif __name__ == \"__main__\":\n    main()\n"
  dependsOn: []
  isVerificationFile: false
  path: gen_snippets.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: gen_snippets.py
layout: document
redirect_from:
- /library/gen_snippets.py
- /library/gen_snippets.py.html
title: gen_snippets.py
---
