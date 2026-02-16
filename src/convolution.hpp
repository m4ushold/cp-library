#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using real_t = double;
using cpx = complex<real_t>;
const long double PI = acosl(-1.L);
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
vector<ll> Conv(const vector<ll> &a, const vector<ll> &b){
    if(a.empty() || b.empty()) return {};
    int sz = a.size() + b.size() - 1, n = 1 << __lg(sz*2-1);
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

vector<ll> ConvMod(const vector<ll> &a, const vector<ll> &b, unsigned long long mod){
    if(a.empty() || b.empty()) return {};
    int sz = a.size() + b.size() - 1, n = 1 << __lg(sz*2-1);
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
