#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int mod = 998'244'353;

int main(){
  cin.tie(0)->sync_with_stdio(0);
  int n,m; cin >> n >> m;
  vector<ll> a(n), b(m);
  for(ll &i:a) cin >> i;
  for(ll &i:b) cin >> i;
  for(auto i:ConvMod(a,b,mod)) cout << i << ' ';
  return 0;
}
