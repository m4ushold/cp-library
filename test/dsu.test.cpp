#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <iostream>
#include "../src/dsu.hpp"

using namespace std;
using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,q; cin >> n >> q;
    dsu d(n);
    for(int i=0;i<q;i++) {
      int a,b,c; cin >> a >> b >> c;
      if(a) cout << d.same(b,c) << endl;
      else d.merge(b,c);
    }
    return 0;
}
