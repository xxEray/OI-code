#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n;
LL K;
int a[N];

std::vector<int> pos[N];

struct Segment {
	int l, r;
	Segment() : l(1), r(0) {}
	Segment(int l_, int r_) : l(l_), r(r_) {}
	bool empty() const { return l > r; }
	int size() const { return std::max(r - l + 1, 0); }
	friend Segment operator&(const Segment &x, const Segment &y) {
		if(x.empty() || y.empty()) return {};
		Segment ret{std::max(x.l, y.l), std::min(x.r, y.r)};
		if(ret.empty()) return {};
		else return ret;
	}
	friend Segment operator|(const Segment &x, const Segment &y) {
		if(x.empty() || y.empty()) return x.empty() ? y : x;
		assert(!(x.r + 1 < y.l || y.r + 1 < x.l));
		return {std::min(x.l, y.l), std::max(x.r, y.r)};
	}
	friend bool operator==(const Segment &x, const Segment &y) { return x.l == y.l && x.r == y.r; }
	Segment operator&=(const Segment &x) { return *this = *this & x; }
};
struct SegmentTree {
	Segment t[N << 2], lazy[N << 2];
	LL sum[N << 2];
	void lazydown(int x) {
		t[x << 1] &= lazy[x], t[x << 1 | 1] &= lazy[x];
		lazy[x << 1] &= lazy[x], lazy[x << 1 | 1] &= lazy[x];
		lazy[x] = {1, n};
	}
	void build(int x = 1, int l = 1, int r = n) {
		// for(int i = 1; i <= n; i++) t[i] = {i, n};
		lazy[x] = {1, n};
		if(l == r) { t[x] = {l, n}, sum[x] = t[x].size(); return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		t[x] = t[x << 1] | t[x << 1 | 1];
	}
	void modify(int ql, int qr, const Segment &qv, int x = 1, int l = 1, int r = n) {
		// printf("modify [%d, %d] (%d, %d)\n", ql, qr, qv.l, qv.r);
		// for(int i = ql; i <= qr; i++) t[i] &= qv;
		if(ql > qr) return;
		if(l == r) { t[x] &= qv; sum[x] = t[x].size(); return; }
		if((t[x] & qv) == t[x]) return;
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = t[x << 1] | t[x << 1 | 1];
		sum[x] = sum[x << 1] + sum[x << 1 | 1];
	}
	LL query(int ql, int qr, const Segment &qv, int x = 1, int l = 1, int r = n) {
		// printf("query [%d, %d] (%d, %d)\n", ql, qr, qv.l, qv.r);
		// LL ret = 0; for(int i = ql; i <= qr; i++) ret += (t[i] & qv).size(); return ret;
		if(ql > qr) return 0;
		if(l == r) return (t[x] & qv).size();
		if((t[x] & qv) == t[x]) return sum[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		LL ret = 0;
		if(ql <= mid) ret += query(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) ret += query(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = t[x << 1] | t[x << 1 | 1];
		sum[x] = sum[x << 1] + sum[x << 1 | 1];
		return ret;
	}
} seg;

int main() {
#ifndef DEBUG
	freopen("warrior.in", "r", stdin);
	freopen("warrior.out", "w", stdout);
#endif
	scanf("%d%lld", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), pos[a[i]].emplace_back(i);
	seg.build();
	std::vector<int> ans;
	for(int i = 1; i <= n; i++) if(!pos[i].empty()) {
		int sz = pos[i].size();
		auto count = [&](int x) -> LL {
			LL sum = 0;
			if(x) {
				for(int j = 0; j < sz - x + 1; j++) sum += seg.query(j ? pos[i][j - 1] + 1 : 1, pos[i][j], {pos[i][j + x - 1], n});
			} else {
				sum += seg.query(1, n, {1, n});
			}
			// printf("count(%d) = %lld\n", x, sum);
			return sum;
		};
		int l = 0, r = sz + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(count(mid) >= K) l = mid + 1;
			else r = mid;
		}
		l--;
		K -= (l == sz ? 0 : count(l + 1));
		if(l) {
			for(int j = 0; j < sz - l + 1; j++) seg.modify(j ? pos[i][j - 1] + 1 : 1, pos[i][j], {pos[i][j + l - 1], j + l == sz ? n : pos[i][j + l] - 1});
			for(int j = sz - l + 1; j < sz; j++) seg.modify(j ? pos[i][j - 1] + 1 : 1, pos[i][j], {});
			seg.modify(pos[i].back() + 1, n, {});
		} else {
			for(int j = 0; j < sz; j++) seg.modify(pos[i][j], pos[i][j], {});
			for(int j = 0; j < sz; j++) seg.modify(j ? pos[i][j - 1] + 1 : 1, pos[i][j] - 1, {j ? pos[i][j - 1] + 1 : 1, pos[i][j] - 1});
			seg.modify(pos[i].back() + 1, n, {pos[i].back() + 1, n});
		}
		// printf("append %d of %ds (K = %lld)\n", l, i, K);
		while(l--) ans.emplace_back(i);
	}
	for(auto x : ans) printf("%d ", x);
	puts("");
	return 0;
} /*
5 3
3 5 2 5 1 

*/