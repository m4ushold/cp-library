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
    _deprecated_at_docs: "docs/segtree.md  <-- (\uC120\uD0DD\uC0AC\uD56D) \uC124\uBA85\
      \uC774 \uAE38\uBA74 \uBCC4\uB3C4 md \uD30C\uC77C\uB85C \uBE84 \uC218\uB3C4 \uC788\
      \uC74C"
    document_title: "\uC138\uADF8\uBA3C\uD2B8 \uD2B8\uB9AC (Segment Tree)"
    links: []
  bundledCode: "#line 2 \"src/segtree.hpp\"\n#include <vector>\n#include <functional>\n\
    \n/**\n * @brief \uC138\uADF8\uBA3C\uD2B8 \uD2B8\uB9AC (Segment Tree)\n * @docs\
    \ docs/segtree.md  <-- (\uC120\uD0DD\uC0AC\uD56D) \uC124\uBA85\uC774 \uAE38\uBA74\
    \ \uBCC4\uB3C4 md \uD30C\uC77C\uB85C \uBE84 \uC218\uB3C4 \uC788\uC74C\n * * \uC810\
    \ \uC5C5\uB370\uC774\uD2B8(Point Update)\uC640 \uAD6C\uAC04 \uCFFC\uB9AC(Range\
    \ Query)\uB97C O(log N)\uC5D0 \uCC98\uB9AC\uD569\uB2C8\uB2E4.\n * * @tparam S\
    \ \uC5F0\uC0B0\uD560 \uD0C0\uC785\n * @tparam op \uC5F0\uC0B0 \uD568\uC218 (Binary\
    \ Operation)\n * @tparam e \uD56D\uB4F1\uC6D0 \uD568\uC218 (Identity Element)\n\
    \ */\ntemplate <class S, S (*op)(S, S), S (*e)()>\nstruct segtree {\n  public:\n\
    \    segtree() : segtree(0) {}\n    explicit segtree(int n) : segtree(std::vector<S>(n,\
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
  code: "#pragma once\n#include <vector>\n#include <functional>\n\n/**\n * @brief\
    \ \uC138\uADF8\uBA3C\uD2B8 \uD2B8\uB9AC (Segment Tree)\n * @docs docs/segtree.md\
    \  <-- (\uC120\uD0DD\uC0AC\uD56D) \uC124\uBA85\uC774 \uAE38\uBA74 \uBCC4\uB3C4\
    \ md \uD30C\uC77C\uB85C \uBE84 \uC218\uB3C4 \uC788\uC74C\n * * \uC810 \uC5C5\uB370\
    \uC774\uD2B8(Point Update)\uC640 \uAD6C\uAC04 \uCFFC\uB9AC(Range Query)\uB97C\
    \ O(log N)\uC5D0 \uCC98\uB9AC\uD569\uB2C8\uB2E4.\n * * @tparam S \uC5F0\uC0B0\uD560\
    \ \uD0C0\uC785\n * @tparam op \uC5F0\uC0B0 \uD568\uC218 (Binary Operation)\n *\
    \ @tparam e \uD56D\uB4F1\uC6D0 \uD568\uC218 (Identity Element)\n */\ntemplate\
    \ <class S, S (*op)(S, S), S (*e)()>\nstruct segtree {\n  public:\n    segtree()\
    \ : segtree(0) {}\n    explicit segtree(int n) : segtree(std::vector<S>(n, e()))\
    \ {}\n    explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {\n  \
    \      log = 0;\n        while ((1U << log) < (unsigned int)(_n)) log++;\n   \
    \     size = 1 << log;\n        d = std::vector<S>(2 * size, e());\n        for\
    \ (int i = 0; i < _n; i++) d[size + i] = v[i];\n        for (int i = size - 1;\
    \ i >= 1; i--) update(i);\n    }\n\n    void set(int p, S x) {\n        p += size;\n\
    \        d[p] = x;\n        for (int i = 1; i <= log; i++) update(p >> i);\n \
    \   }\n\n    S get(int p) const {\n        return d[p + size];\n    }\n\n    S\
    \ prod(int l, int r) const {\n        S a = e(), b = e();\n        for(l += size,\
    \ r += size; l < r; l >>= 1, r >>= 1) {\n            if (l & 1) a = op(a, d[l++]);\n\
    \            if (r & 1) b = op(d[--r], b);\n        }\n        return op(a, b);\n\
    \    }\n\n  private:\n    int _n, size, log;\n    std::vector<S> d;\n    void\
    \ update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }\n};"
  dependsOn: []
  isVerificationFile: false
  path: src/segtree.hpp
  requiredBy: []
  timestamp: '2026-02-13 16:48:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/segtree.test.cpp
documentation_of: src/segtree.hpp
layout: document
redirect_from:
- /library/src/segtree.hpp
- /library/src/segtree.hpp.html
title: "\uC138\uADF8\uBA3C\uD2B8 \uD2B8\uB9AC (Segment Tree)"
---
