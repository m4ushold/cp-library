#pragma once
#include <vector>
#include <functional>

// @snippet segtree
template <class S, S (*op)(S, S), S (*e)()>
struct segtree {
  int _n, size, log;
  std::vector<S> d;

  segtree(int n) : segtree(std::vector<S>(n, e())) {}
  segtree(const std::vector<S> &v) : _n(v.size()), size(1), log(0) {
    while(size < _n) size <<= 1, ++log;
    d = std::vector<S>(size << 1, e());
    for(int i = 0; i < _n; i++) d[size + i] = v[i];
    for(int i = size - 1; i; i--) update(i);
  }

  void update(int i) {d[i] = op(d[i<<1], d[i<<1|1]);}

  void set(int i, S x) {
    i += size;
    d[i] = x;
    while(i >>= 1) update(i);
  }

  S get(int i) {
    return d[size + i];
  }

  S prod(int l, int r) {
    S a = e(), b = e();
    for(l += size, r += size; l < r; l >>= 1, r >>= 1) {
      if(l & 1) a = op(a, d[l++]);
      if(r & 1) b = op(d[--r], b);
    }
    return op(a,b);
  }

  S all_prod() {
    return d[1];
  }
};
