---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/convolution.hpp
    title: src/convolution.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod
    links:
    - https://judge.yosupo.jp/problem/convolution_mod
  bundledCode: "#line 1 \"test/convolution_mod.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\
    \n\n#include <bits/stdc++.h>\n#line 2 \"src/convolution.hpp\"\nusing namespace\
    \ std;\nusing ll = long long;\n\n// ================= [ 0. Common & FFT Base ]\
    \ =================\nusing real_t = double;\nusing cpx = complex<real_t>;\nconst\
    \ real_t PI = acos(-1);\nvoid FFT(vector<cpx> &a, bool inv_fft=false){\n    int\
    \ n = a.size();\n    for(int i=1, j=0, bit; i<n; i++){\n        for(bit=n/2; j>=bit;\
    \ bit/=2) j -= bit;\n        if(i < (j += bit)) swap(a[i], a[j]);\n    }\n   \
    \ vector<cpx> root(n/2);\n    long double ang = 2 * acosl(-1) / n * (inv_fft ?\
    \ -1 : 1);\n    for(int i=0; i<n/2; i++) root[i] = cpx(cosl(ang*i), sinl(ang*i));\n\
    \    for(int i=2; i<=n; i*=2){\n        int step = n / i;\n        for(int j=0;\
    \ j<n; j+=i){\n            for(int k=0; k<i/2; k++){\n                auto u =\
    \ a[j+k], v = a[j+k+i/2] * root[step*k];\n                a[j+k] = u + v; a[j+k+i/2]\
    \ = u - v;\n            }\n        }\n    }\n    if(inv_fft) for(int i=0; i<n;\
    \ i++) a[i] /= n;\n}\n\n// ================= [ 1. Conv (Normal Multiply) ] =================\n\
    // \uC77C\uBC18 \uC815\uC218 \uACF1\uC148 (\uACB0\uACFC\uAC12 long long \uBC94\
    \uC704 \uB0B4)\nvector<ll> Conv(const vector<ll> &a, const vector<ll> &b){\r\n\
    \    if(a.empty() || b.empty()) return {};\r\n    int sz = a.size() + b.size()\
    \ - 1, n = 1;\n    while(n<sz) n<<=1;\n    vector<cpx> in(n), out(n);\r\n    for(int\
    \ i=0; i<a.size(); i++) in[i].real(a[i]);\r\n    for(int i=0; i<b.size(); i++)\
    \ in[i].imag(b[i]);\r\n    FFT(in);\r\n    for(auto &i : in) i *= i;\r\n    for(int\
    \ i=0; i<n; i++) out[i] = in[-i&(n-1)] - conj(in[i]);\r\n    FFT(out);\r\n   \
    \ vector<ll> res(sz);\r\n    for(int i=0; i<sz; i++) res[i] = llround(imag(out[i])\
    \ / (4 * n));\r\n    return res;\r\n}\n\n// ================= [ 2. ConvMod (Arbitrary\
    \ Modulo) ] =================\n// \uC784\uC758\uC758 \uBAA8\uB4C8\uB7EC(1e9+7\
    \ \uB4F1) \uACF1\uC148. (Splitting FFT \uC774\uC6A9)\n// \uC0AC\uC6A9\uBC95: vector<ll>\
    \ res = ConvMod(a, b, 1000000007);\nvector<ll> ConvMod(const vector<ll> &a, const\
    \ vector<ll> &b, unsigned long long mod){\n    if(a.empty() || b.empty()) return\
    \ {};\n    int sz = a.size() + b.size() - 1, n = 1;\n    while(n<sz) n<<=1;\n\
    \    vector<cpx> l(n), r(n), outs(n), outl(n);\n    for(int i=0; i<a.size(); i++)\
    \ l[i] = cpx(a[i] >> 15, a[i] & 32767);\n    for(int i=0; i<b.size(); i++) r[i]\
    \ = cpx(b[i] >> 15, b[i] & 32767);\n    FFT(l); FFT(r);\n    for(int i=0; i<n;\
    \ i++){\n        int j = -i & (n - 1);\n        outl[j] = (l[i] + conj(l[j]))\
    \ * r[i] / (2. * n);\n        outs[j] = (l[i] - conj(l[j])) * r[i] / (2. * n)\
    \ / 1i;\n    }\n    FFT(outl); FFT(outs);\n    vector<ll> res(sz);\n    for(int\
    \ i=0; i<res.size(); i++){\n        ll av = llround(real(outl[i])), cv = llround(imag(outs[i]));\n\
    \        ll bv = llround(imag(outl[i])) + llround(real(outs[i]));\n        res[i]\
    \ = ((((av % mod << 15) + bv) % mod << 15) + cv) % mod;\n    }\n    return res;\n\
    }\n\n// ================= [ 3. FWHT (Bitwise) ] =================\n// XOR, OR,\
    \ AND Convolution\nll Power(ll base, ll exp, ll mod) {\n    ll res = 1; base %=\
    \ mod;\n    while (exp) {\n        if (exp & 1) res = res * base % mod;\n    \
    \    base = base * base % mod;\n        exp >>= 1;\n    } return res;\n}\nll ModInv(ll\
    \ n, ll mod) { return Power(n, mod - 2, mod); }\n\ntemplate<char op> void FWHT(vector<ll>\
    \ &a, bool inv, ll mod) {\n    int n = a.size();\n    for (int len = 1; len <\
    \ n; len <<= 1) {\n        for (int i = 0; i < n; i += 2 * len) {\n          \
    \  for (int j = 0; j < len; j++) {\n                ll u = a[i + j], v = a[i +\
    \ len + j];\n                if (op == '^') { // XOR\n                    a[i\
    \ + j] = (u + v) % mod;\n                    a[i + len + j] = (u - v + mod) %\
    \ mod;\n                } else if (op == '|') { // OR\n                    if\
    \ (!inv) a[i + len + j] = (v + u) % mod;\n                    else      a[i +\
    \ len + j] = (v - u + mod) % mod;\n                } else if (op == '&') { //\
    \ AND\n                    if (!inv) a[i + j] = (u + v) % mod;\n             \
    \       else      a[i + j] = (u - v + mod) % mod;\n                }\n       \
    \     }\n        }\n    }\n    if (op == '^' && inv) {\n        ll inv_n = ModInv(n,\
    \ mod);\n        for (auto &x : a) x = x * inv_n % mod;\n    }\n}\n\ntemplate<char\
    \ op> vector<ll> ConvFWHT(vector<ll> a, vector<ll> b, ll mod) {\n    int n = 1;\
    \ while (n < max(a.size(), b.size())) n <<= 1;\n    a.resize(n); b.resize(n);\n\
    \    FWHT<op>(a, 0, mod); FWHT<op>(b, 0, mod);\n    for (int i = 0; i < n; i++)\
    \ a[i] = a[i] * b[i] % mod;\n    FWHT<op>(a, 1, mod);\n    return a;\n}\n\n//\
    \ ================= [ NTT for 998244353 ] =================\n// 998244353 = 119\
    \ * 2^23 + 1, Primitive Root = 3\n// 998,244,353 = 119 * 2^23 + 1, w 3 | 2,281,701,377\
    \ = 17 * 2^27 + 1, w 3\n// 167,772,161 =  10 * 2^25 + 1, w 3 | 2,483,027,969 =\
    \ 37 * 2^26 + 1, w 3\n// 469,762,049 =  26 * 2^26 + 1, w 3 | 2,013,265,921 = 15\
    \ * 2^27 + 1, w 31\n\nconst ll MOD = 998244353;\nconst ll G = 3;\n\n// \uAC70\uB4ED\
    \uC81C\uACF1 (Modular Exponentiation)\nll power(ll base, ll exp) {\n    ll res\
    \ = 1;\n    base %= MOD;\n    while (exp > 0) {\n        if (exp % 2 == 1) res\
    \ = (res * base) % MOD;\n        base = (base * base) % MOD;\n        exp /= 2;\n\
    \    }\n    return res;\n}\n\n// \uBAA8\uB4C8\uB7EC \uC5ED\uC6D0 (Fermat's Little\
    \ Theorem)\nll modInverse(ll n) {\n    return power(n, MOD - 2);\n}\n\n// NTT\
    \ (Number Theoretic Transform)\nvoid NTT(vector<ll>& a, bool invert) {\n    int\
    \ n = a.size();\n\n    // 1. Bit Reversal Permutation\n    for (int i = 1, j =\
    \ 0; i < n; i++) {\n        int bit = n >> 1;\n        for (; j & bit; bit >>=\
    \ 1) j ^= bit;\n        j ^= bit;\n        if (i < j) swap(a[i], a[j]);\n    }\n\
    \n    // 2. Butterfly Operations\n    for (int len = 2; len <= n; len <<= 1) {\n\
    \        ll wlen = power(G, (MOD - 1) / len);\n        if (invert) wlen = modInverse(wlen);\n\
    \n        for (int i = 0; i < n; i += len) {\n            ll w = 1;\n        \
    \    for (int j = 0; j < len / 2; j++) {\n                ll u = a[i + j];\n \
    \               ll v = (a[i + j + len / 2] * w) % MOD;\n                a[i +\
    \ j] = (u + v) % MOD;\n                a[i + j + len / 2] = (u - v + MOD) % MOD;\n\
    \                w = (w * wlen) % MOD;\n            }\n        }\n    }\n\n  \
    \  // 3. Inverse Scaling\n    if (invert) {\n        ll n_inv = modInverse(n);\n\
    \        for (ll& x : a) x = (x * n_inv) % MOD;\n    }\n}\n\n// Convolution Function\n\
    vector<ll> NTTConv(vector<ll> const& a, vector<ll> const& b) {\n    vector<ll>\
    \ fa(a.begin(), a.end()), fb(b.begin(), b.end());\n    int n = 1;\n    while (n\
    \ < a.size() + b.size()) n <<= 1;\n    \n    fa.resize(n);\n    fb.resize(n);\n\
    \n    NTT(fa, false);\n    NTT(fb, false);\n    \n    for (int i = 0; i < n; i++)\n\
    \        fa[i] = (fa[i] * fb[i]) % MOD;\n        \n    NTT(fa, true);\n\n    //\
    \ \uBB38\uC81C \uC694\uAD6C\uC0AC\uD56D\uC5D0 \uB9DE\uCDB0 \uC0AC\uC774\uC988\
    \ \uC870\uC808 (N + M - 1)\n    fa.resize(a.size() + b.size() - 1);\n    return\
    \ fa;\n}\n#line 5 \"test/convolution_mod.test.cpp\"\n\nusing namespace std;\n\
    using ll = long long;\n\nint main() {\n  cin.tie(0)->sync_with_stdio(0);\n  int\
    \ n,m; cin >> n >> m;\n  vector<ll> a(n), b(m);\n  for(ll &i:a) cin >> i;\n  for(ll\
    \ &i:b) cin >> i;\n  for(auto i:NTTConv(a,b)) cout << i << ' ';\n  return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#include\
    \ <bits/stdc++.h>\n#include \"../src/convolution.hpp\"\n\nusing namespace std;\n\
    using ll = long long;\n\nint main() {\n  cin.tie(0)->sync_with_stdio(0);\n  int\
    \ n,m; cin >> n >> m;\n  vector<ll> a(n), b(m);\n  for(ll &i:a) cin >> i;\n  for(ll\
    \ &i:b) cin >> i;\n  for(auto i:NTTConv(a,b)) cout << i << ' ';\n  return 0;\n\
    }\n"
  dependsOn:
  - src/convolution.hpp
  isVerificationFile: true
  path: test/convolution_mod.test.cpp
  requiredBy: []
  timestamp: '2026-02-16 19:30:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/convolution_mod.test.cpp
layout: document
redirect_from:
- /verify/test/convolution_mod.test.cpp
- /verify/test/convolution_mod.test.cpp.html
title: test/convolution_mod.test.cpp
---
