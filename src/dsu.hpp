#pragma once
#include <bits/stdc++.h>

// @snippet dsu
struct dsu {
  int _n;
  std::vector<int> p;
  dsu(int n) : _n(n), p(n, -1) {}
  int leader(int a) {
    return p[a] < 0 ? a : p[a] = leader(p[a]);
  }
  bool same(int a, int b) {
    return leader(a) == leader(b);
  }
  int size(int a) {
    return -p[leader(a)];
  }
  int merge(int a, int b) {
    a = leader(a), b = leader(b);
    if(a == b) return a;
    if(-p[a] < -p[b]) std::swap(a,b);
    p[a] += p[b];
    return p[b] = a;
  }
};
