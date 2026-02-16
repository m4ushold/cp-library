---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution_and.test.cpp
    title: test/convolution_and.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/convolution_xor.test.cpp
    title: test/convolution_xor.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/convolution.hpp\"\n#include <bits/stdc++.h>\nusing namespace\
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
    \ a[i] = a[i] * b[i] % mod;\n    FWHT<op>(a, 1, mod);\n    return a;\n}\n"
  code: "#include <bits/stdc++.h>\nusing namespace std;\nusing ll = long long;\n\n\
    // ================= [ 0. Common & FFT Base ] =================\nusing real_t\
    \ = double;\nusing cpx = complex<real_t>;\nconst real_t PI = acos(-1);\nvoid FFT(vector<cpx>\
    \ &a, bool inv_fft=false){\n    int n = a.size();\n    for(int i=1, j=0, bit;\
    \ i<n; i++){\n        for(bit=n/2; j>=bit; bit/=2) j -= bit;\n        if(i < (j\
    \ += bit)) swap(a[i], a[j]);\n    }\n    vector<cpx> root(n/2);\n    long double\
    \ ang = 2 * acosl(-1) / n * (inv_fft ? -1 : 1);\n    for(int i=0; i<n/2; i++)\
    \ root[i] = cpx(cosl(ang*i), sinl(ang*i));\n    for(int i=2; i<=n; i*=2){\n  \
    \      int step = n / i;\n        for(int j=0; j<n; j+=i){\n            for(int\
    \ k=0; k<i/2; k++){\n                auto u = a[j+k], v = a[j+k+i/2] * root[step*k];\n\
    \                a[j+k] = u + v; a[j+k+i/2] = u - v;\n            }\n        }\n\
    \    }\n    if(inv_fft) for(int i=0; i<n; i++) a[i] /= n;\n}\n\n// =================\
    \ [ 1. Conv (Normal Multiply) ] =================\n// \uC77C\uBC18 \uC815\uC218\
    \ \uACF1\uC148 (\uACB0\uACFC\uAC12 long long \uBC94\uC704 \uB0B4)\nvector<ll>\
    \ Conv(const vector<ll> &a, const vector<ll> &b){\r\n    if(a.empty() || b.empty())\
    \ return {};\r\n    int sz = a.size() + b.size() - 1, n = 1;\n    while(n<sz)\
    \ n<<=1;\n    vector<cpx> in(n), out(n);\r\n    for(int i=0; i<a.size(); i++)\
    \ in[i].real(a[i]);\r\n    for(int i=0; i<b.size(); i++) in[i].imag(b[i]);\r\n\
    \    FFT(in);\r\n    for(auto &i : in) i *= i;\r\n    for(int i=0; i<n; i++) out[i]\
    \ = in[-i&(n-1)] - conj(in[i]);\r\n    FFT(out);\r\n    vector<ll> res(sz);\r\n\
    \    for(int i=0; i<sz; i++) res[i] = llround(imag(out[i]) / (4 * n));\r\n   \
    \ return res;\r\n}\n\n// ================= [ 2. ConvMod (Arbitrary Modulo) ] =================\n\
    // \uC784\uC758\uC758 \uBAA8\uB4C8\uB7EC(1e9+7 \uB4F1) \uACF1\uC148. (Splitting\
    \ FFT \uC774\uC6A9)\n// \uC0AC\uC6A9\uBC95: vector<ll> res = ConvMod(a, b, 1000000007);\n\
    vector<ll> ConvMod(const vector<ll> &a, const vector<ll> &b, unsigned long long\
    \ mod){\n    if(a.empty() || b.empty()) return {};\n    int sz = a.size() + b.size()\
    \ - 1, n = 1;\n    while(n<sz) n<<=1;\n    vector<cpx> l(n), r(n), outs(n), outl(n);\n\
    \    for(int i=0; i<a.size(); i++) l[i] = cpx(a[i] >> 15, a[i] & 32767);\n   \
    \ for(int i=0; i<b.size(); i++) r[i] = cpx(b[i] >> 15, b[i] & 32767);\n    FFT(l);\
    \ FFT(r);\n    for(int i=0; i<n; i++){\n        int j = -i & (n - 1);\n      \
    \  outl[j] = (l[i] + conj(l[j])) * r[i] / (2. * n);\n        outs[j] = (l[i] -\
    \ conj(l[j])) * r[i] / (2. * n) / 1i;\n    }\n    FFT(outl); FFT(outs);\n    vector<ll>\
    \ res(sz);\n    for(int i=0; i<res.size(); i++){\n        ll av = llround(real(outl[i])),\
    \ cv = llround(imag(outs[i]));\n        ll bv = llround(imag(outl[i])) + llround(real(outs[i]));\n\
    \        res[i] = ((((av % mod << 15) + bv) % mod << 15) + cv) % mod;\n    }\n\
    \    return res;\n}\n\n// ================= [ 3. FWHT (Bitwise) ] =================\n\
    // XOR, OR, AND Convolution\nll Power(ll base, ll exp, ll mod) {\n    ll res =\
    \ 1; base %= mod;\n    while (exp) {\n        if (exp & 1) res = res * base %\
    \ mod;\n        base = base * base % mod;\n        exp >>= 1;\n    } return res;\n\
    }\nll ModInv(ll n, ll mod) { return Power(n, mod - 2, mod); }\n\ntemplate<char\
    \ op> void FWHT(vector<ll> &a, bool inv, ll mod) {\n    int n = a.size();\n  \
    \  for (int len = 1; len < n; len <<= 1) {\n        for (int i = 0; i < n; i +=\
    \ 2 * len) {\n            for (int j = 0; j < len; j++) {\n                ll\
    \ u = a[i + j], v = a[i + len + j];\n                if (op == '^') { // XOR\n\
    \                    a[i + j] = (u + v) % mod;\n                    a[i + len\
    \ + j] = (u - v + mod) % mod;\n                } else if (op == '|') { // OR\n\
    \                    if (!inv) a[i + len + j] = (v + u) % mod;\n             \
    \       else      a[i + len + j] = (v - u + mod) % mod;\n                } else\
    \ if (op == '&') { // AND\n                    if (!inv) a[i + j] = (u + v) %\
    \ mod;\n                    else      a[i + j] = (u - v + mod) % mod;\n      \
    \          }\n            }\n        }\n    }\n    if (op == '^' && inv) {\n \
    \       ll inv_n = ModInv(n, mod);\n        for (auto &x : a) x = x * inv_n %\
    \ mod;\n    }\n}\n\ntemplate<char op> vector<ll> ConvFWHT(vector<ll> a, vector<ll>\
    \ b, ll mod) {\n    int n = 1; while (n < max(a.size(), b.size())) n <<= 1;\n\
    \    a.resize(n); b.resize(n);\n    FWHT<op>(a, 0, mod); FWHT<op>(b, 0, mod);\n\
    \    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % mod;\n    FWHT<op>(a, 1,\
    \ mod);\n    return a;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/convolution.hpp
  requiredBy: []
  timestamp: '2026-02-16 18:37:01+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/convolution_and.test.cpp
  - test/convolution_xor.test.cpp
documentation_of: src/convolution.hpp
layout: document
redirect_from:
- /library/src/convolution.hpp
- /library/src/convolution.hpp.html
title: src/convolution.hpp
---
