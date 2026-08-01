#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;

struct SegTree { // Segment Tree
	LL t[N << 2], mn[N << 2];
	void build() { for(int i = 0; i < (N << 2); i++) t[i] = n, mn[i] = LLINF; }
	void set_min(int ql, int qr, LL qmin, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) {
			if(qmin < t[x]) t[x] = qmin, mn[x] = qmin;
			return;
		}
		int mid = l + ((r - l) >> 1); // (l + r) / 2
		mn[x << 1] = std::min(mn[x << 1], mn[x]);
		mn[x << 1 | 1] = std::min(mn[x << 1 | 1], mn[x]);
		t[x << 1] = std::min(t[x << 1], mn[x]);
		t[x << 1 | 1] = std::min(t[x << 1 | 1], mn[x]);
		mn[x] = LLINF;
		if(ql <= mid) set_min(ql, qr, qmin, x << 1, l, mid);
		if(qr > mid) set_min(ql, qr, qmin, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]);
	}
	LL query(int qind, int x = 1, int l = 1, int r = n) {
		if(l == r) return t[x];
		int mid = l + ((r - l) >> 1); // (l + r) / 2
		mn[x << 1] = std::min(mn[x << 1], mn[x]);
		mn[x << 1 | 1] = std::min(mn[x << 1 | 1], mn[x]);
		t[x << 1] = std::min(t[x << 1], mn[x]);
		t[x << 1 | 1] = std::min(t[x << 1 | 1], mn[x]);
		mn[x] = LLINF;
		if(qind <= mid) return query(qind, x << 1, l, mid);
		else return query(qind, x << 1 | 1, mid + 1, r);
	}
} trr, trc; // tree-row, tree-col

int main() {
	std::scanf("%d%d", &n, &m);
	trr.build(), trc.build();
	LL ans = 0;
	for(int i = 1; i <= m; i++) {
		int t, x;
		std::scanf("%d%d", &t, &x);
		if(t == 1) {
			LL len = trc.query(x);
			// std::printf("len = %d\n", len);
			ans += len - 2;
			trr.set_min(1, len, x);
		} else {
			LL len = trr.query(x);
			// std::printf("len = %d\n", len);
			ans += len - 2;
			trc.set_min(1, len, x);
		}
	}
	std::printf("%lld\n", (LL)(n - 2) * (n - 2) - ans);
	return 0;
}