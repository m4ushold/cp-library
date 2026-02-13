---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/segtree.hpp
    title: "\uC138\uADF8\uBA3C\uD2B8 \uD2B8\uB9AC (Segment Tree)"
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
    \ <functional>\n\n/**\n * @brief \uC138\uADF8\uBA3C\uD2B8 \uD2B8\uB9AC (Segment\
    \ Tree)\n * @docs docs/segtree.md  <-- (\uC120\uD0DD\uC0AC\uD56D) \uC124\uBA85\
    \uC774 \uAE38\uBA74 \uBCC4\uB3C4 md \uD30C\uC77C\uB85C \uBE84 \uC218\uB3C4 \uC788\
    \uC74C\n * * \uC810 \uC5C5\uB370\uC774\uD2B8(Point Update)\uC640 \uAD6C\uAC04\
    \ \uCFFC\uB9AC(Range Query)\uB97C O(log N)\uC5D0 \uCC98\uB9AC\uD569\uB2C8\uB2E4\
    .\n * * @tparam S \uC5F0\uC0B0\uD560 \uD0C0\uC785\n * @tparam op \uC5F0\uC0B0\
    \ \uD568\uC218 (Binary Operation)\n * @tparam e \uD56D\uB4F1\uC6D0 \uD568\uC218\
    \ (Identity Element)\n */\ntemplate <class S, S (*op)(S, S), S (*e)()>\nstruct\
    \ segtree {\n  public:\n    segtree() : segtree(0) {}\n    explicit segtree(int\
    \ n) : segtree(std::vector<S>(n, e())) {}\n    explicit segtree(const std::vector<S>&\
    \ v) : _n(int(v.size())) {\n        log = 0;\n        while ((1U << log) < (unsigned\
    \ int)(_n)) log++;\n        size = 1 << log;\n        d = std::vector<S>(2 * size,\
    \ e());\n        for (int i = 0; i < _n; i++) d[size + i] = v[i];\n        for\
    \ (int i = size - 1; i >= 1; i--) update(i);\n    }\n\n    void set(int p, S x)\
    \ {\n        p += size;\n        d[p] = x;\n        for (int i = 1; i <= log;\
    \ i++) update(p >> i);\n    }\n\n    S get(int p) const {\n        return d[p\
    \ + size];\n    }\n\n    S prod(int l, int r) const {\n        S sml = e(), smr\
    \ = e();\n        l += size;\n        r += size;\n        while (l < r) {\n  \
    \          if (l & 1) sml = op(sml, d[l++]);\n            if (r & 1) smr = op(d[--r],\
    \ smr);\n            l >>= 1;\n            r >>= 1;\n        }\n        return\
    \ op(sml, smr);\n    }\n\n  private:\n    int _n, size, log;\n    std::vector<S>\
    \ d;\n    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }\n};\n#line\
    \ 5 \"test/segtree.test.cpp\"\n\nusing namespace std;\nusing ll = long long;\n\
    \nll op(ll a, ll b) { return a + b; }\nll e() { return 0; }\n\nint main() {\n\
    \    cin.tie(0)->sync_with_stdio(0);\n    int n,q; cin >> n >> q;\n    vector<ll>\
    \ v(n);\n    for(ll &i:v) cin >> i;\n\n    segtree<ll,op,e> seg(v);\n    for(int\
    \ i=0;i<q;i++) {\n        ll a,b,c; cin >> a >> b >> c;\n        if(a == 0) seg.set(b,seg.get(b)\
    \ + c);\n        else cout << seg.prod(b,c) << '\\n';\n    }\n    return 0;\n\
    }\n"
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
  timestamp: '2026-02-13 14:27:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/segtree.test.cpp
layout: document
redirect_from:
- /verify/test/segtree.test.cpp
- /verify/test/segtree.test.cpp.html
title: test/segtree.test.cpp
---
