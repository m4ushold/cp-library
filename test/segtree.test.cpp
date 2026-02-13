#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <iostream>
#include "../src/segtree.hpp"

using namespace std;
using ll = long long;

ll op(ll a, ll b) { return a + b; }
ll e() { return 0; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,q; cin >> n >> q;
    vector<ll> v(n);
    for(ll &i:v) cin >> i;

    segtree<ll,op,e> seg(v);
    for(int i=0;i<q;i++) {
        ll a,b,c; cin >> a >> b >> c;
        if(a == 0) seg.set(b,seg.get(b) + c);
        else cout << seg.prod(b,c) << '\n';
    }
    return 0;
}