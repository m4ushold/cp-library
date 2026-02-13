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
    \ {\n  public:\n    segtree() : segtree(0) {}\n    explicit segtree(int n) : segtree(std::vector<S>(n,\
    \ e())) {}\n    explicit segtree(const std::vector<S>& v) : _n(int(v.size()))\
    \ {\n        log = 0;\n        while ((1U << log) < (unsigned int)(_n)) log++;\n\
    \        size = 1 << log;\n        d = std::vector<S>(2 * size, e());\n      \
    \  for (int i = 0; i < _n; i++) d[size + i] = v[i];\n        for (int i = size\
    \ - 1; i >= 1; i--) update(i);\n    }\n\n    void set(int p, S x) {\n        p\
    \ += size;\n        d[p] = x;\n        for (int i = 1; i <= log; i++) update(p\
    \ >> i);\n    }\n\n    S get(int p) const {\n        return d[p + size];\n   \
    \ }\n\n    S prod(int l, int r) const {\n        S a = e(), b = e();\n       \
    \ for(l += size, r += size; l < r; l >>= 1, r >>= 1) {\n            if (l & 1)\
    \ a = op(a, d[l++]);\n            if (r & 1) b = op(d[--r], b);\n        }\n \
    \       return op(a, b);\n    }\n\n  private:\n    int _n, size, log;\n    std::vector<S>\
    \ d;\n    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }\n};\n"
  code: "#pragma once\n#include <vector>\n#include <functional>\n\n// @snippet segtree\n\
    template <class S, S (*op)(S, S), S (*e)()>\nstruct segtree {\n  public:\n   \
    \ segtree() : segtree(0) {}\n    explicit segtree(int n) : segtree(std::vector<S>(n,\
    \ e())) {}\n    explicit segtree(const std::vector<S>& v) : _n(int(v.size()))\
    \ {\n        log = 0;\n        while ((1U << log) < (unsigned int)(_n)) log++;\n\
    \        size = 1 << log;\n        d = std::vector<S>(2 * size, e());\n      \
    \  for (int i = 0; i < _n; i++) d[size + i] = v[i];\n        for (int i = size\
    \ - 1; i >= 1; i--) update(i);\n    }\n\n    void set(int p, S x) {\n        p\
    \ += size;\n        d[p] = x;\n        for (int i = 1; i <= log; i++) update(p\
    \ >> i);\n    }\n\n    S get(int p) const {\n        return d[p + size];\n   \
    \ }\n\n    S prod(int l, int r) const {\n        S a = e(), b = e();\n       \
    \ for(l += size, r += size; l < r; l >>= 1, r >>= 1) {\n            if (l & 1)\
    \ a = op(a, d[l++]);\n            if (r & 1) b = op(d[--r], b);\n        }\n \
    \       return op(a, b);\n    }\n\n  private:\n    int _n, size, log;\n    std::vector<S>\
    \ d;\n    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }\n};"
  dependsOn: []
  isVerificationFile: false
  path: src/segtree.hpp
  requiredBy: []
  timestamp: '2026-02-13 17:05:27+09:00'
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
