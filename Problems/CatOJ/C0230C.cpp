#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];
int bl[N], br[N];

LL f[N], g[N];
std::vector<int> to1[N], to0[N];
struct SegmentTree {
	LL t[N << 2], lazy[N << 2];
	inline void setlazy(int x, LL v) { lazy[x] += v, t[x] += v; }
	inline void lazydown(int x) { setlazy(x << 1, lazy[x]), setlazy(x << 1 | 1, lazy[x]), lazy[x] = 0; }
	inline void add(int ql, int qr, LL qv) { add(ql, qr, qv, 1, 0, n); }
	void add(int ql, int qr, LL qv, int x, int l, int r) {
		if(ql <= l && r <= qr) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
	inline LL querymax(int ql, int qr) { return querymax(ql, qr, 1, 0, n); }
	LL querymax(int ql, int qr, int x, int l, int r) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return querymax(ql, qr, x << 1, l, mid);
		else if(ql > mid) return querymax(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::max(querymax(ql, qr, x << 1, l, mid), querymax(ql, qr, x << 1 | 1, mid + 1, r));
	}
	LL get(int qind) { return querymax(qind, qind); }
	void set(int qind, LL qv) { add(qind, qind, qv - get(qind)); }
	void clear(int qind) { add(qind, qind, -get(qind)); }
} seg, segg, segf;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d%d", &bl[i], &br[i]);
	for(int i = 1; i <= n; i++) seg.add(i, i, a[i]);
	for(int i = 1; i <= n; i++) {
		if(br[i] < a[i]) continue;
		int l = i, r = n + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(seg.querymax(i, mid) < bl[i]) l = mid + 1;
			else r = mid;
		}
		to1[l].push_back(i);
		l = i, r = n + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(seg.querymax(i, mid) <= br[i]) l = mid + 1;
			else r = mid;
		}
		to0[l].push_back(i);
	}
	f[0] = 0;
	std::vector<int> stk;
	for(int i = 1; i <= n; i++) {
		// stk
		while(!stk.empty() && a[stk.back()] <= a[i]) stk.pop_back(), segf.clear(stk.size());
		// calc g
		// printf("%d:\n", i);
		// printf("    to1: "); for(int j : to1[i]) printf("%d ", j); puts("");
		// printf("    to0: "); for(int j : to0[i]) printf("%d ", j); puts("");
		for(int j : to1[i]) segg.add(0, j - 1, 1);
		for(int j : to0[i]) segg.add(0, j - 1, -1);
		int j = (stk.empty() ? 0 : stk.back());
		g[i] = segg.querymax(j, i - 1);
		// calc f & update g
		a[0] = br[i];
		auto it = std::lower_bound(stk.begin(), stk.end(), 0, [&](int x, int y) { return a[x] > a[y]; });
		int l = it - stk.begin();
		a[0] = bl[i];
		it = std::upper_bound(stk.begin(), stk.end(), 0, [&](int x, int y) { return a[x] > a[y]; });
		int r = (it - stk.begin()) - 1;
		if(l <= r && l >= 0 && r < (int)stk.size()) segf.add(l, r, 1);
		segf.add(stk.size(), stk.size(), g[i]), stk.push_back(i);
		f[i] = segf.querymax(0, (int)stk.size() - 1);
		// update f
		segg.add(i, i, f[i]);
		// debug
		// printf("%d: f=%lld, g=%lld\n", i, f[i], g[i]);
	}
	printf("%lld\n", f[n]);
	return 0;
} /*
5
3 2 1 3 1
3 3
2 4
5 5
5 5
3 4
*/