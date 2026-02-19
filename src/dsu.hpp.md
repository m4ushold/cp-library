---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/dsu.test.cpp
    title: test/dsu.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/dsu.hpp\"\n#include <bits/stdc++.h>\n\n// @snippet dsu\n\
    struct dsu {\n  int _n;\n  std::vector<int> p;\n  dsu(int n) : _n(n), p(n, -1)\
    \ {}\n  int leader(int a) {\n    return p[a] < 0 ? a : p[a] = leader(p[a]);\n\
    \  }\n  bool same(int a, int b) {\n    return leader(a) == leader(b);\n  }\n \
    \ int size(int a) {\n    return -p[leader(a)];\n  }\n  int merge(int a, int b)\
    \ {\n    a = leader(a), b = leader(b);\n    if(a == b) return a;\n    if(-p[a]\
    \ < -p[b]) std::swap(a,b);\n    p[a] += p[b];\n    return p[b] = a;\n  }\n};\n"
  code: "#pragma once\n#include <bits/stdc++.h>\n\n// @snippet dsu\nstruct dsu {\n\
    \  int _n;\n  std::vector<int> p;\n  dsu(int n) : _n(n), p(n, -1) {}\n  int leader(int\
    \ a) {\n    return p[a] < 0 ? a : p[a] = leader(p[a]);\n  }\n  bool same(int a,\
    \ int b) {\n    return leader(a) == leader(b);\n  }\n  int size(int a) {\n   \
    \ return -p[leader(a)];\n  }\n  int merge(int a, int b) {\n    a = leader(a),\
    \ b = leader(b);\n    if(a == b) return a;\n    if(-p[a] < -p[b]) std::swap(a,b);\n\
    \    p[a] += p[b];\n    return p[b] = a;\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/dsu.hpp
  requiredBy: []
  timestamp: '2026-02-19 19:12:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/dsu.test.cpp
documentation_of: src/dsu.hpp
layout: document
redirect_from:
- /library/src/dsu.hpp
- /library/src/dsu.hpp.html
title: src/dsu.hpp
---
