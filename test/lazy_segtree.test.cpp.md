---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/lazy_segtree.hpp
    title: src/lazy_segtree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_add_range_min
    links:
    - https://judge.yosupo.jp/problem/range_add_range_min
  bundledCode: "#line 1 \"test/lazy_segtree.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/range_add_range_min\"\
    \n\n#include <bits/stdc++.h>\n#line 5 \"src/lazy_segtree.hpp\"\n\ntemplate <class\
    \ S,\n          S (*op)(S, S),\n          S (*e)(),\n          class F,\n    \
    \      S (*mapping)(F, S),\n          F (*composition)(F, F),\n          F (*id)()>\n\
    struct lazy_segtree {\n\n  public:\n    lazy_segtree() : lazy_segtree(0) {}\n\
    \    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}\n\
    \    explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())), size(1),\
    \ log(0) {\n        while(size < _n) size <<= 1, ++log;\n        d = std::vector<S>(size\
    \ << 1, e());\n        d = std::vector<S>(2 * size, e());\n        lz = std::vector<F>(size,\
    \ id());\n        for (int i = 0; i < _n; i++) d[size + i] = v[i];\n        for\
    \ (int i = size - 1; i >= 1; i--) {\n            update(i);\n        }\n    }\n\
    \n    void set(int p, S x) {\n        assert(0 <= p && p < _n);\n        p +=\
    \ size;\n        for (int i = log; i >= 1; i--) push(p >> i);\n        d[p] =\
    \ x;\n        for (int i = 1; i <= log; i++) update(p >> i);\n    }\n\n    S get(int\
    \ p) {\n        assert(0 <= p && p < _n);\n        p += size;\n        for (int\
    \ i = log; i >= 1; i--) push(p >> i);\n        return d[p];\n    }\n\n    S prod(int\
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
    \       all_apply(2 * k + 1, lz[k]);\n        lz[k] = id();\n    }\n};\n\n#line\
    \ 5 \"test/lazy_segtree.test.cpp\"\n\nusing namespace std;\nusing ll = long long;\n\
    \nll op(ll a, ll b) {return min(a,b);}\nll e() {return LLONG_MAX;}\nll mapping(ll\
    \ a, ll b) {return a+b;}\nll composite(ll a, ll b) {return a+b;}\nll id() {return\
    \ 0;}\n\nint main() {\n  cin.tie(0)->sync_with_stdio(0);\n  int n,q; cin >> n\
    \ >> q;\n  vector<ll> v(n);\n  for(ll &i:v) cin >> i;\n  lazy_segtree<ll,op,e,ll,mapping,composite,id>\
    \ seg(v);\n  for(ll i=0,a,b,c,d;i<q;i++) {\n    cin >> a >> b >> c;\n    if(a)\
    \ cout << seg.prod(b,c) << endl;\n    else cin >> d, seg.apply(b,c,d);\n  }\n\
    \  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_add_range_min\"\n\
    \n#include <bits/stdc++.h>\n#include \"../src/lazy_segtree.hpp\"\n\nusing namespace\
    \ std;\nusing ll = long long;\n\nll op(ll a, ll b) {return min(a,b);}\nll e()\
    \ {return LLONG_MAX;}\nll mapping(ll a, ll b) {return a+b;}\nll composite(ll a,\
    \ ll b) {return a+b;}\nll id() {return 0;}\n\nint main() {\n  cin.tie(0)->sync_with_stdio(0);\n\
    \  int n,q; cin >> n >> q;\n  vector<ll> v(n);\n  for(ll &i:v) cin >> i;\n  lazy_segtree<ll,op,e,ll,mapping,composite,id>\
    \ seg(v);\n  for(ll i=0,a,b,c,d;i<q;i++) {\n    cin >> a >> b >> c;\n    if(a)\
    \ cout << seg.prod(b,c) << endl;\n    else cin >> d, seg.apply(b,c,d);\n  }\n\
    \  return 0;\n}\n"
  dependsOn:
  - src/lazy_segtree.hpp
  isVerificationFile: true
  path: test/lazy_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-02-23 00:21:01+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/lazy_segtree.test.cpp
layout: document
redirect_from:
- /verify/test/lazy_segtree.test.cpp
- /verify/test/lazy_segtree.test.cpp.html
title: test/lazy_segtree.test.cpp
---
