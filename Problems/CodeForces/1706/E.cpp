#include <cstdio>
#include <algorithm>
#include <cstring>
#ifndef ATCODER_SEGTREE_HPP
#define ATCODER_SEGTREE_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

#ifndef ATCODER_INTERNAL_BITOP_HPP
#define ATCODER_INTERNAL_BITOP_HPP 1

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace atcoder {

namespace internal {

// @param n `0 <= n`
// @return minimum non-negative `x` s.t. `n <= 2**x`
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
constexpr int bsf_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
int bsf(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

}  // namespace internal

}  // namespace atcoder

#endif  // ATCODER_INTERNAL_BITOP_HPP


namespace atcoder {

template <class S, S (*op)(S, S), S (*e)()> struct segtree {
  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

}  // namespace atcoder

#endif  // ATCODER_SEGTREE_HPP

const int N = 1e5 + 5;

int n, m, Q;

int fa[N * 2];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int son[N * 2][2];
int go[N * 2][21];
int ans[N * 2];

int mymax(int x, int y) { return std::max(x, y); }
int myzero() { return 0; }

void preprocess() {
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n * 2 - 1; i++)
			go[i][j] = go[go[i][j - 1]][j - 1];
}

int d[3 * N];
void dfs(int u) {
	if(!u) return;
	d[son[u][0]] = d[son[u][1]] = d[u] + 1;
	dfs(son[u][0]), dfs(son[u][1]);
}

int lca(int x, int y) {
	if(d[x] > d[y]) std::swap(x, y);
	int dis = d[y] - d[x];
	for(int i = 0; dis; i++, dis >>= 1)
		if(dis & 1)
			y = go[y][i];
	if(x == y) return x;
	for(int i = 20; i >= 0; i--)
		if(go[x][i] != go[y][i]) {
			x = go[x][i];
			y = go[y][i];
		}
	return go[x][0];
}

int main() {
	// freopen("out.txt", "w", stdout);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &m, &Q);
		for(int i = 1; i <= n * 2 - 1; i++) d[i] = 0, go[i][0] = 0, son[i][0] = son[i][1] = 0, fa[i] = i;
		int c = n;
		for(int i = 1; i <= m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			u = find(u), v = find(v);
			if(u != v) {
				c++;
				ans[c] = i;
				fa[u] = fa[v] = c;
				go[u][0] = go[v][0] = c;
				son[c][0] = u, son[c][1] = v;
			}
		}
		preprocess();
		// for(int i = 1; i <= n * 2 - 1; i++) printf("fa[%d] = %d\n", i, go[i][0]);
		d[n * 2 - 1] = 1;
		dfs(n * 2 - 1);
		atcoder::segtree<int, mymax, myzero> seg(n + 1);
		for(int i = 2; i <= n; i++) seg.set(i, lca(i - 1, i));
		// for(int i = 1; i <= n; i++) printf("seg[%d] = %d\n", i, seg.get(i));
		while(Q--) {
			int l, r;
			scanf("%d%d", &l, &r);
			// printf("l = %d, r = %d\n", l, r);
			printf("%d ", l == r ? 0 : ans[seg.prod(l + 1, r + 1)]);
		}
		puts("");
	}
	return 0;
} /*
3
2 1 2
1 2
1 1
1 2
5 5 5
1 2
1 3
2 4
3 4
3 5
1 4
3 4
2 2
2 5
3 5
3 2 1
1 3
2 3
1 3

*/