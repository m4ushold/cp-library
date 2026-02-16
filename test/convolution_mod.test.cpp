#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <bits/stdc++.h>
#include "../src/convolution.hpp"

using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n,m; cin >> n >> m;
  vector<ll> a(n), b(m);
  for(ll &i:a) cin >> i;
  for(ll &i:b) cin >> i;
  for(auto i:NTTConv(a,b)) cout << i << ' ';
  return 0;
}
