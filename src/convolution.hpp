#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ================= [ 0. Common & FFT Base ] =================
using real_t = double;
using cpx = complex<real_t>;
const real_t PI = acos(-1);
void FFT(vector<cpx> &a, bool inv_fft=false){
    int n = a.size();
    for(int i=1, j=0, bit; i<n; i++){
        for(bit=n/2; j>=bit; bit/=2) j -= bit;
        if(i < (j += bit)) swap(a[i], a[j]);
    }
    vector<cpx> root(n/2);
    long double ang = 2 * acosl(-1) / n * (inv_fft ? -1 : 1);
    for(int i=0; i<n/2; i++) root[i] = cpx(cosl(ang*i), sinl(ang*i));
    for(int i=2; i<=n; i*=2){
        int step = n / i;
        for(int j=0; j<n; j+=i){
            for(int k=0; k<i/2; k++){
                auto u = a[j+k], v = a[j+k+i/2] * root[step*k];
                a[j+k] = u + v; a[j+k+i/2] = u - v;
            }
        }
    }
    if(inv_fft) for(int i=0; i<n; i++) a[i] /= n;
}

// ================= [ 1. Conv (Normal Multiply) ] =================
// 일반 정수 곱셈 (결과값 long long 범위 내)
vector<ll> Conv(const vector<ll> &a, const vector<ll> &b){
    if(a.empty() || b.empty()) return {};
    int sz = a.size() + b.size() - 1, n = 1;
    while(n<sz) n<<=1;
    vector<cpx> in(n), out(n);
    for(int i=0; i<a.size(); i++) in[i].real(a[i]);
    for(int i=0; i<b.size(); i++) in[i].imag(b[i]);
    FFT(in);
    for(auto &i : in) i *= i;
    for(int i=0; i<n; i++) out[i] = in[-i&(n-1)] - conj(in[i]);
    FFT(out);
    vector<ll> res(sz);
    for(int i=0; i<sz; i++) res[i] = llround(imag(out[i]) / (4 * n));
    return res;
}

// ================= [ 2. ConvMod (Arbitrary Modulo) ] =================
// 임의의 모듈러(1e9+7 등) 곱셈. (Splitting FFT 이용)
// 사용법: vector<ll> res = ConvMod(a, b, 1000000007);
vector<ll> ConvMod(const vector<ll> &a, const vector<ll> &b, unsigned long long mod){
    if(a.empty() || b.empty()) return {};
    int sz = a.size() + b.size() - 1, n = 1;
    while(n<sz) n<<=1;
    vector<cpx> l(n), r(n), outs(n), outl(n);
    for(int i=0; i<a.size(); i++) l[i] = cpx(a[i] >> 15, a[i] & 32767);
    for(int i=0; i<b.size(); i++) r[i] = cpx(b[i] >> 15, b[i] & 32767);
    FFT(l); FFT(r);
    for(int i=0; i<n; i++){
        int j = -i & (n - 1);
        outl[j] = (l[i] + conj(l[j])) * r[i] / (2. * n);
        outs[j] = (l[i] - conj(l[j])) * r[i] / (2. * n) / 1i;
    }
    FFT(outl); FFT(outs);
    vector<ll> res(sz);
    for(int i=0; i<res.size(); i++){
        ll av = llround(real(outl[i])), cv = llround(imag(outs[i]));
        ll bv = llround(imag(outl[i])) + llround(real(outs[i]));
        res[i] = ((((av % mod << 15) + bv) % mod << 15) + cv) % mod;
    }
    return res;
}

// ================= [ 3. FWHT (Bitwise) ] =================
// XOR, OR, AND Convolution
ll Power(ll base, ll exp, ll mod) {
    ll res = 1; base %= mod;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    } return res;
}
ll ModInv(ll n, ll mod) { return Power(n, mod - 2, mod); }

template<char op> void FWHT(vector<ll> &a, bool inv, ll mod) {
    int n = a.size();
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                ll u = a[i + j], v = a[i + len + j];
                if (op == '^') { // XOR
                    a[i + j] = (u + v) % mod;
                    a[i + len + j] = (u - v + mod) % mod;
                } else if (op == '|') { // OR
                    if (!inv) a[i + len + j] = (v + u) % mod;
                    else      a[i + len + j] = (v - u + mod) % mod;
                } else if (op == '&') { // AND
                    if (!inv) a[i + j] = (u + v) % mod;
                    else      a[i + j] = (u - v + mod) % mod;
                }
            }
        }
    }
    if (op == '^' && inv) {
        ll inv_n = ModInv(n, mod);
        for (auto &x : a) x = x * inv_n % mod;
    }
}

template<char op> vector<ll> ConvFWHT(vector<ll> a, vector<ll> b, ll mod) {
    int n = 1; while (n < max(a.size(), b.size())) n <<= 1;
    a.resize(n); b.resize(n);
    FWHT<op>(a, 0, mod); FWHT<op>(b, 0, mod);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % mod;
    FWHT<op>(a, 1, mod);
    return a;
}
