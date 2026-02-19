---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/segtree.test.cpp
    title: test/segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/segtree.hpp\"\n#include <vector>\n#include <functional>\n\
    \n// @snippet segtree\ntemplate <class S, S (*op)(S, S), S (*e)()>\nstruct segtree\
    \ {\n  int _n, size, log;\n  std::vector<S> d;\n\n  segtree(int n) : segtree(std::vector<S>(n,\
    \ e())) {}\n  segtree(const std::vector<S> &v) : _n(v.size()), size(1), log(0)\
    \ {\n    while(size < _n) size <<= 1, ++log;\n    d = std::vector<S>(size << 1,\
    \ e());\n    for(int i = 0; i < _n; i++) d[size + i] = v[i];\n    for(int i =\
    \ size - 1; i; i--) update(i);\n  }\n\n  void update(int i) {d[i] = op(d[i<<1],\
    \ d[i<<1|1]);}\n\n  void set(int i, S x) {\n    i += size;\n    d[i] = x;\n  \
    \  while(i >>= 1) update(i);\n  }\n\n  S get(int i) {\n    return d[size + i];\n\
    \  }\n\n  S prod(int l, int r) {\n    S a = e(), b = e();\n    for(l += size,\
    \ r += size; l < r; l >>= 1, r >>= 1) {\n      if(l & 1) a = op(a, d[l++]);\n\
    \      if(r & 1) b = op(d[--r], b);\n    }\n    return op(a,b);\n  }\n\n  S all_prod()\
    \ {\n    return d[1];\n  }\n};\n"
  code: "#pragma once\n#include <vector>\n#include <functional>\n\n// @snippet segtree\n\
    template <class S, S (*op)(S, S), S (*e)()>\nstruct segtree {\n  int _n, size,\
    \ log;\n  std::vector<S> d;\n\n  segtree(int n) : segtree(std::vector<S>(n, e()))\
    \ {}\n  segtree(const std::vector<S> &v) : _n(v.size()), size(1), log(0) {\n \
    \   while(size < _n) size <<= 1, ++log;\n    d = std::vector<S>(size << 1, e());\n\
    \    for(int i = 0; i < _n; i++) d[size + i] = v[i];\n    for(int i = size - 1;\
    \ i; i--) update(i);\n  }\n\n  void update(int i) {d[i] = op(d[i<<1], d[i<<1|1]);}\n\
    \n  void set(int i, S x) {\n    i += size;\n    d[i] = x;\n    while(i >>= 1)\
    \ update(i);\n  }\n\n  S get(int i) {\n    return d[size + i];\n  }\n\n  S prod(int\
    \ l, int r) {\n    S a = e(), b = e();\n    for(l += size, r += size; l < r; l\
    \ >>= 1, r >>= 1) {\n      if(l & 1) a = op(a, d[l++]);\n      if(r & 1) b = op(d[--r],\
    \ b);\n    }\n    return op(a,b);\n  }\n\n  S all_prod() {\n    return d[1];\n\
    \  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/segtree.hpp
  requiredBy: []
  timestamp: '2026-02-19 19:35:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/segtree.test.cpp
documentation_of: src/segtree.hpp
layout: document
redirect_from:
- /library/src/segtree.hpp
- /library/src/segtree.hpp.html
title: src/segtree.hpp
---
