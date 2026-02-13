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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.11.14/x64/lib/python3.11/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.11.14/x64/lib/python3.11/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 96, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "import os\nimport json\nimport re\n\n# ================= \uC124\uC815 =================\n\
    SRC_DIR = \"./src\"\n\n# 1. VS Code\uC6A9 \uCD9C\uB825 \uACBD\uB85C\nVSCODE_OUTPUT\
    \ = \"snippets/vscode\"\n\n# 2. Neovim\uC6A9 \uCD9C\uB825 \uACBD\uB85C (UltiSnips/SnipMate\
    \ \uD638\uD658)\nNEOVIM_OUTPUT = \"snippets/nvim\"\n# =======================================\n\
    \ndef parse_file(filepath):\n    \"\"\"\uD30C\uC77C\uC744 \uC77D\uC5B4\uC11C @snippet\
    \ \uD0DC\uADF8\uBCC4\uB85C \uCF54\uB4DC\uB97C \uCD94\uCD9C\uD568\"\"\"\n    with\
    \ open(filepath, 'r', encoding='utf-8') as f:\n        lines = f.readlines()\n\
    \n    snippets = {}\n    current_trigger = None\n    current_code = []\n    \n\
    \    # \uC815\uADDC\uD45C\uD604\uC2DD: // @snippet \uD2B8\uB9AC\uAC70\uBA85\n\
    \    trigger_pattern = re.compile(r'^\\s*//\\s*@snippet\\s+(\\w+)')\n\n    for\
    \ line in lines:\n        match = trigger_pattern.search(line)\n        if match:\n\
    \            if current_trigger:\n                snippets[current_trigger] =\
    \ current_code\n            current_trigger = match.group(1)\n            current_code\
    \ = []\n            continue \n\n        if current_trigger:\n            # \uC8FC\
    \uC11D \uBC0F \uBE48 \uC904 \uCC98\uB9AC\uB294 \uCDE8\uD5A5\uAECF (\uC5EC\uAE30\
    \uC11C\uB294 \uADF8\uB300\uB85C \uC800\uC7A5)\n            current_code.append(line.rstrip())\n\
    \n    if current_trigger:\n        snippets[current_trigger] = current_code\n\
    \        \n    return snippets\n\ndef generate_vscode_json(all_snippets):\n  \
    \  \"\"\"VS Code\uC6A9 JSON \uD30C\uC77C \uC0DD\uC131\"\"\"\n    vscode_snippets\
    \ = {}\n    for trigger, code_lines in all_snippets.items():\n        vscode_snippets[trigger]\
    \ = {\n            \"prefix\": trigger,\n            \"body\": code_lines,\n \
    \           \"description\": f\"CP Library: {trigger}\"\n        }\n    \n   \
    \ os.makedirs(os.path.dirname(VSCODE_OUTPUT), exist_ok=True)\n    with open(VSCODE_OUTPUT,\
    \ 'w', encoding='utf-8') as f:\n        json.dump(vscode_snippets, f, indent=4,\
    \ ensure_ascii=False)\n    print(f\"\u2705 VS Code: Generated {len(all_snippets)}\
    \ snippets -> {VSCODE_OUTPUT}\")\n\ndef generate_neovim_snipmate(all_snippets):\n\
    \    \"\"\"Neovim (UltiSnips/SnipMate)\uC6A9 \uD30C\uC77C \uC0DD\uC131\"\"\"\n\
    \    os.makedirs(os.path.dirname(NEOVIM_OUTPUT), exist_ok=True)\n    \n    with\
    \ open(NEOVIM_OUTPUT, 'w', encoding='utf-8') as f:\n        f.write(\"# Generated\
    \ by cp-library tools\\n\\n\")\n        \n        for trigger, code_lines in all_snippets.items():\n\
    \            f.write(f\"snippet {trigger}\\n\")\n            # \uB4E4\uC5EC\uC4F0\
    \uAE30\uB294 \uD0ED\uC774\uB098 \uACF5\uBC31\uC73C\uB85C \uC720\uC9C0\uB428\n\
    \            for line in code_lines:\n                f.write(f\"\\t{line}\\n\"\
    ) # \uBCF8\uBB38 \uC55E\uC5D0 \uD0ED \uD558\uB098 \uCD94\uAC00 (SnipMate \uBB38\
    \uBC95)\n            f.write(\"endsnippet\\n\\n\")\n            \n    print(f\"\
    \u2705 Neovim : Generated {len(all_snippets)} snippets -> {NEOVIM_OUTPUT}\")\n\
    \ndef main():\n    all_snippets = {}\n    \n    for root, dirs, files in os.walk(SRC_DIR):\n\
    \        for file in files:\n            if file.endswith((\".hpp\", \".cpp\"\
    )):\n                filepath = os.path.join(root, file)\n                file_snippets\
    \ = parse_file(filepath)\n                \n                for trigger, code\
    \ in file_snippets.items():\n                    all_snippets[trigger] = code\n\
    \n    # \uB450 \uAC00\uC9C0 \uD3EC\uB9F7 \uBAA8\uB450 \uC0DD\uC131\n    generate_vscode_json(all_snippets)\n\
    \    generate_neovim_snipmate(all_snippets)\n\nif __name__ == \"__main__\":\n\
    \    main()"
  dependsOn: []
  isVerificationFile: false
  path: tools/gen_snippets.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tools/gen_snippets.py
layout: document
redirect_from:
- /library/tools/gen_snippets.py
- /library/tools/gen_snippets.py.html
title: tools/gen_snippets.py
---
