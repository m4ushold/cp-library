---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/lazy_segtree.test.cpp
    title: test/lazy_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/lazy_segtree.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <functional>\n#include <vector>\n\ntemplate <class S,\n          S (*op)(S,\
    \ S),\n          S (*e)(),\n          class F,\n          S (*mapping)(F, S),\n\
    \          F (*composition)(F, F),\n          F (*id)()>\nstruct lazy_segtree\
    \ {\n\n  public:\n    lazy_segtree() : lazy_segtree(0) {}\n    explicit lazy_segtree(int\
    \ n) : lazy_segtree(std::vector<S>(n, e())) {}\n    explicit lazy_segtree(const\
    \ std::vector<S>& v) : _n(int(v.size())), size(1), log(0) {\n        while(size\
    \ < _n) size <<= 1, ++log;\n        d = std::vector<S>(size << 1, e());\n    \
    \    d = std::vector<S>(2 * size, e());\n        lz = std::vector<F>(size, id());\n\
    \        for (int i = 0; i < _n; i++) d[size + i] = v[i];\n        for (int i\
    \ = size - 1; i >= 1; i--) {\n            update(i);\n        }\n    }\n\n   \
    \ void set(int p, S x) {\n        assert(0 <= p && p < _n);\n        p += size;\n\
    \        for (int i = log; i >= 1; i--) push(p >> i);\n        d[p] = x;\n   \
    \     for (int i = 1; i <= log; i++) update(p >> i);\n    }\n\n    S get(int p)\
    \ {\n        assert(0 <= p && p < _n);\n        p += size;\n        for (int i\
    \ = log; i >= 1; i--) push(p >> i);\n        return d[p];\n    }\n\n    S prod(int\
    \ l, int r) {\n        assert(0 <= l && l <= r && r <= _n);\n        if (l ==\
    \ r) return e();\n\n        l += size;\n        r += size;\n\n        for (int\
    \ i = log; i >= 1; i--) {\n            if (((l >> i) << i) != l) push(l >> i);\n\
    \            if (((r >> i) << i) != r) push((r - 1) >> i);\n        }\n\n    \
    \    S sml = e(), smr = e();\n        while (l < r) {\n            if (l & 1)\
    \ sml = op(sml, d[l++]);\n            if (r & 1) smr = op(d[--r], smr);\n    \
    \        l >>= 1;\n            r >>= 1;\n        }\n\n        return op(sml, smr);\n\
    \    }\n\n    S all_prod() { return d[1]; }\n\n    void apply(int p, F f) {\n\
    \        assert(0 <= p && p < _n);\n        p += size;\n        for (int i = log;\
    \ i >= 1; i--) push(p >> i);\n        d[p] = mapping(f, d[p]);\n        for (int\
    \ i = 1; i <= log; i++) update(p >> i);\n    }\n    void apply(int l, int r, F\
    \ f) {\n        assert(0 <= l && l <= r && r <= _n);\n        if (l == r) return;\n\
    \n        l += size;\n        r += size;\n\n        for (int i = log; i >= 1;\
    \ i--) {\n            if (((l >> i) << i) != l) push(l >> i);\n            if\
    \ (((r >> i) << i) != r) push((r - 1) >> i);\n        }\n\n        {\n       \
    \     int l2 = l, r2 = r;\n            while (l < r) {\n                if (l\
    \ & 1) all_apply(l++, f);\n                if (r & 1) all_apply(--r, f);\n   \
    \             l >>= 1;\n                r >>= 1;\n            }\n            l\
    \ = l2;\n            r = r2;\n        }\n\n        for (int i = 1; i <= log; i++)\
    \ {\n            if (((l >> i) << i) != l) update(l >> i);\n            if (((r\
    \ >> i) << i) != r) update((r - 1) >> i);\n        }\n    }\n\n  private:\n  \
    \  int _n, size, log;\n    std::vector<S> d;\n    std::vector<F> lz;\n\n    void\
    \ update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }\n    void all_apply(int\
    \ k, F f) {\n        d[k] = mapping(f, d[k]);\n        if (k < size) lz[k] = composition(f,\
    \ lz[k]);\n    }\n    void push(int k) {\n        all_apply(2 * k, lz[k]);\n \
    \       all_apply(2 * k + 1, lz[k]);\n        lz[k] = id();\n    }\n};\n\n"
  code: "#include <algorithm>\n#include <cassert>\n#include <functional>\n#include\
    \ <vector>\n\ntemplate <class S,\n          S (*op)(S, S),\n          S (*e)(),\n\
    \          class F,\n          S (*mapping)(F, S),\n          F (*composition)(F,\
    \ F),\n          F (*id)()>\nstruct lazy_segtree {\n\n  public:\n    lazy_segtree()\
    \ : lazy_segtree(0) {}\n    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n,\
    \ e())) {}\n    explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())),\
    \ size(1), log(0) {\n        while(size < _n) size <<= 1, ++log;\n        d =\
    \ std::vector<S>(size << 1, e());\n        d = std::vector<S>(2 * size, e());\n\
    \        lz = std::vector<F>(size, id());\n        for (int i = 0; i < _n; i++)\
    \ d[size + i] = v[i];\n        for (int i = size - 1; i >= 1; i--) {\n       \
    \     update(i);\n        }\n    }\n\n    void set(int p, S x) {\n        assert(0\
    \ <= p && p < _n);\n        p += size;\n        for (int i = log; i >= 1; i--)\
    \ push(p >> i);\n        d[p] = x;\n        for (int i = 1; i <= log; i++) update(p\
    \ >> i);\n    }\n\n    S get(int p) {\n        assert(0 <= p && p < _n);\n   \
    \     p += size;\n        for (int i = log; i >= 1; i--) push(p >> i);\n     \
    \   return d[p];\n    }\n\n    S prod(int l, int r) {\n        assert(0 <= l &&\
    \ l <= r && r <= _n);\n        if (l == r) return e();\n\n        l += size;\n\
    \        r += size;\n\n        for (int i = log; i >= 1; i--) {\n            if\
    \ (((l >> i) << i) != l) push(l >> i);\n            if (((r >> i) << i) != r)\
    \ push((r - 1) >> i);\n        }\n\n        S sml = e(), smr = e();\n        while\
    \ (l < r) {\n            if (l & 1) sml = op(sml, d[l++]);\n            if (r\
    \ & 1) smr = op(d[--r], smr);\n            l >>= 1;\n            r >>= 1;\n  \
    \      }\n\n        return op(sml, smr);\n    }\n\n    S all_prod() { return d[1];\
    \ }\n\n    void apply(int p, F f) {\n        assert(0 <= p && p < _n);\n     \
    \   p += size;\n        for (int i = log; i >= 1; i--) push(p >> i);\n       \
    \ d[p] = mapping(f, d[p]);\n        for (int i = 1; i <= log; i++) update(p >>\
    \ i);\n    }\n    void apply(int l, int r, F f) {\n        assert(0 <= l && l\
    \ <= r && r <= _n);\n        if (l == r) return;\n\n        l += size;\n     \
    \   r += size;\n\n        for (int i = log; i >= 1; i--) {\n            if (((l\
    \ >> i) << i) != l) push(l >> i);\n            if (((r >> i) << i) != r) push((r\
    \ - 1) >> i);\n        }\n\n        {\n            int l2 = l, r2 = r;\n     \
    \       while (l < r) {\n                if (l & 1) all_apply(l++, f);\n     \
    \           if (r & 1) all_apply(--r, f);\n                l >>= 1;\n        \
    \        r >>= 1;\n            }\n            l = l2;\n            r = r2;\n \
    \       }\n\n        for (int i = 1; i <= log; i++) {\n            if (((l >>\
    \ i) << i) != l) update(l >> i);\n            if (((r >> i) << i) != r) update((r\
    \ - 1) >> i);\n        }\n    }\n\n  private:\n    int _n, size, log;\n    std::vector<S>\
    \ d;\n    std::vector<F> lz;\n\n    void update(int k) { d[k] = op(d[2 * k], d[2\
    \ * k + 1]); }\n    void all_apply(int k, F f) {\n        d[k] = mapping(f, d[k]);\n\
    \        if (k < size) lz[k] = composition(f, lz[k]);\n    }\n    void push(int\
    \ k) {\n        all_apply(2 * k, lz[k]);\n        all_apply(2 * k + 1, lz[k]);\n\
    \        lz[k] = id();\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: src/lazy_segtree.hpp
  requiredBy: []
  timestamp: '2026-02-23 00:17:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/lazy_segtree.test.cpp
documentation_of: src/lazy_segtree.hpp
layout: document
redirect_from:
- /library/src/lazy_segtree.hpp
- /library/src/lazy_segtree.hpp.html
title: src/lazy_segtree.hpp
---
