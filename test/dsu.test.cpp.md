---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/dsu.hpp
    title: src/dsu.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"test/dsu.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\
    \n\n#include <iostream>\n#line 2 \"src/dsu.hpp\"\n#include <bits/stdc++.h>\n\n\
    // @snippet dsu\nstruct dsu {\n  int _n;\n  std::vector<int> p;\n  dsu(int n)\
    \ : _n(n), p(n, -1) {}\n  int leader(int a) {\n    return p[a] < 0 ? a : p[a]\
    \ = leader(p[a]);\n  }\n  bool same(int a, int b) {\n    return leader(a) == leader(b);\n\
    \  }\n  int size(int a) {\n    return -p[leader(a)];\n  }\n  int merge(int a,\
    \ int b) {\n    a = leader(a), b = leader(b);\n    if(a == b) return a;\n    if(-p[a]\
    \ < -p[b]) std::swap(a,b);\n    p[a] += p[b];\n    return p[b] = a;\n  }\n};\n\
    #line 5 \"test/dsu.test.cpp\"\n\nusing namespace std;\nusing ll = long long;\n\
    \nint main() {\n    cin.tie(0)->sync_with_stdio(0);\n    int n,q; cin >> n >>\
    \ q;\n    dsu d(n);\n    for(int i=0;i<q;i++) {\n      int a,b,c; cin >> a >>\
    \ b >> c;\n      if(a) cout << d.same(b,c) << endl;\n      else d.merge(b,c);\n\
    \    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ <iostream>\n#include \"../src/dsu.hpp\"\n\nusing namespace std;\nusing ll =\
    \ long long;\n\nint main() {\n    cin.tie(0)->sync_with_stdio(0);\n    int n,q;\
    \ cin >> n >> q;\n    dsu d(n);\n    for(int i=0;i<q;i++) {\n      int a,b,c;\
    \ cin >> a >> b >> c;\n      if(a) cout << d.same(b,c) << endl;\n      else d.merge(b,c);\n\
    \    }\n    return 0;\n}\n"
  dependsOn:
  - src/dsu.hpp
  isVerificationFile: true
  path: test/dsu.test.cpp
  requiredBy: []
  timestamp: '2026-02-19 19:12:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/dsu.test.cpp
layout: document
redirect_from:
- /verify/test/dsu.test.cpp
- /verify/test/dsu.test.cpp.html
title: test/dsu.test.cpp
---
