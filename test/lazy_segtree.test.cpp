#define PROBLEM "https://judge.yosupo.jp/problem/range_add_range_min"

#include <bits/stdc++.h>
#include "../src/lazysegtree.hpp"

using namespace std;
using ll = long long;

ll op(ll a, ll b) {return min(a,b);}
ll e() {return LLONG_MAX;}
ll mapping(ll a, ll b) {return a+b;}
ll composite(ll a, ll b) {return a+b;}
ll id() {return 0;}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n,q; cin >> n >> q;
  vector<ll> v(n);
  for(ll &i:v) cin >> i;
  lazy_segtree<ll,op,e,ll,mapping,composite,id> seg(v);
  for(ll i=0,a,b,c,d;i<q;i++) {
    cin >> a >> b >> c;
    if(a) cout << seg.prod(b,c) << endl;
    else cin >> d, seg.apply(b,c,d);
  }
  return 0;
}
