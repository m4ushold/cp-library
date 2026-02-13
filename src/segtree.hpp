#pragma once
#include <vector>
#include <functional>

/**
 * @brief 세그먼트 트리 (Segment Tree)
 * @docs docs/segtree.md  <-- (선택사항) 설명이 길면 별도 md 파일로 뺄 수도 있음
 * * 점 업데이트(Point Update)와 구간 쿼리(Range Query)를 O(log N)에 처리합니다.
 * * @tparam S 연산할 타입
 * @tparam op 연산 함수 (Binary Operation)
 * @tparam e 항등원 함수 (Identity Element)
 */
template <class S, S (*op)(S, S), S (*e)()>
struct segtree {
  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = 0;
        while ((1U << log) < (unsigned int)(_n)) log++;
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) update(i);
    }

    void set(int p, S x) {
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) const {
        return d[p + size];
    }

    S prod(int l, int r) const {
        S a = e(), b = e();
        for(l |= size, r |= size; l < r; l >= 1, r >= 1) {
            if (l & 1) a = op(a, d[l++]);
            if (r & 1) a = op(d[--r], b);
        }
        return op(a, b);
    }

  private:
    int _n, size, log;
    std::vector<S> d;
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};