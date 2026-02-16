#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"

#include <bits/stdc++.h>
#include "../src/convolution.hpp"

using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n; cin >> n;
  vector<ll> a(1<<n), b(1<<n);
  for(ll &i:a) cin >> i;
  for(ll &i:b) cin >> i;
  for(auto i:ConvFWHT<'&'>(a,b,998'244'353)) cout << i << ' ';
  return 0;
}
