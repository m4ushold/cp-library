---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/segtree.hpp
    title: src/segtree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"test/segtree.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\
    \n\n#include <iostream>\n#line 2 \"src/segtree.hpp\"\n#include <vector>\n#include\
    \ <functional>\n\n// @snippet segtree\ntemplate <class S, S (*op)(S, S), S (*e)()>\n\
    struct segtree {\n  public:\n    segtree() : segtree(0) {}\n    explicit segtree(int\
    \ n) : segtree(std::vector<S>(n, e())) {}\n    explicit segtree(const std::vector<S>&\
    \ v) : _n(int(v.size())) {\n        log = 0;\n        while ((1U << log) < (unsigned\
    \ int)(_n)) log++;\n        size = 1 << log;\n        d = std::vector<S>(2 * size,\
    \ e());\n        for (int i = 0; i < _n; i++) d[size + i] = v[i];\n        for\
    \ (int i = size - 1; i >= 1; i--) update(i);\n    }\n\n    void set(int p, S x)\
    \ {\n        p += size;\n        d[p] = x;\n        for (int i = 1; i <= log;\
    \ i++) update(p >> i);\n    }\n\n    S get(int p) const {\n        return d[p\
    \ + size];\n    }\n\n    S prod(int l, int r) const {\n        S a = e(), b =\
    \ e();\n        for(l += size, r += size; l < r; l >>= 1, r >>= 1) {\n       \
    \     if (l & 1) a = op(a, d[l++]);\n            if (r & 1) b = op(d[--r], b);\n\
    \        }\n        return op(a, b);\n    }\n\n  private:\n    int _n, size, log;\n\
    \    std::vector<S> d;\n    void update(int k) { d[k] = op(d[2 * k], d[2 * k +\
    \ 1]); }\n};\n#line 5 \"test/segtree.test.cpp\"\n\nusing namespace std;\nusing\
    \ ll = long long;\n\nll op(ll a, ll b) { return a + b; }\nll e() { return 0; }\n\
    \nint main() {\n    cin.tie(0)->sync_with_stdio(0);\n    int n,q; cin >> n >>\
    \ q;\n    vector<ll> v(n);\n    for(ll &i:v) cin >> i;\n\n    segtree<ll,op,e>\
    \ seg(v);\n    for(int i=0;i<q;i++) {\n        ll a,b,c; cin >> a >> b >> c;\n\
    \        if(a == 0) seg.set(b,seg.get(b) + c);\n        else cout << seg.prod(b,c)\
    \ << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include <iostream>\n#include \"../src/segtree.hpp\"\n\nusing namespace std;\n\
    using ll = long long;\n\nll op(ll a, ll b) { return a + b; }\nll e() { return\
    \ 0; }\n\nint main() {\n    cin.tie(0)->sync_with_stdio(0);\n    int n,q; cin\
    \ >> n >> q;\n    vector<ll> v(n);\n    for(ll &i:v) cin >> i;\n\n    segtree<ll,op,e>\
    \ seg(v);\n    for(int i=0;i<q;i++) {\n        ll a,b,c; cin >> a >> b >> c;\n\
    \        if(a == 0) seg.set(b,seg.get(b) + c);\n        else cout << seg.prod(b,c)\
    \ << '\\n';\n    }\n    return 0;\n}"
  dependsOn:
  - src/segtree.hpp
  isVerificationFile: true
  path: test/segtree.test.cpp
  requiredBy: []
  timestamp: '2026-02-13 17:05:27+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/segtree.test.cpp
layout: document
redirect_from:
- /verify/test/segtree.test.cpp
- /verify/test/segtree.test.cpp.html
title: test/segtree.test.cpp
---
