#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;

int n, m;

struct SegmentTree {
	LL t[N << 2], lazy[N << 2];
	void set_lazy(int x, LL v, int len) { t[x] += len * v, lazy[x] += v; }
	void lazy_down(int x, int l, int r) {
		int mid = (l + r) >> 1;
		set_lazy(x << 1, lazy[x], mid - l + 1), set_lazy(x << 1 | 1, lazy[x], r - mid);
		lazy[x] = 0;
	}
	void modify(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) { set_lazy(x, qv, r - l + 1); return; }
		int mid = (l + r) >> 1;
		lazy_down(x, l, r);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = t[x << 1] + t[x << 1 | 1];
	}
	LL query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		LL ret = 0;
		lazy_down(x, l, r);
		if(ql <= mid) ret += query(ql, qr, x << 1, l, mid);
		if(qr > mid) ret += query(ql, qr, x << 1 | 1, mid + 1, r);
		return ret;
	}
} seg;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) { LL x; scanf("%lld", &x); seg.modify(i, i, x); }
	while(m--) {
		int t;
		scanf("%d", &t);
		if(t == 1) { int l, r; LL v; scanf("%d%d%lld", &l, &r, &v); seg.modify(l, r, v); }
		else if(t == 2) { int l, r; scanf("%d%d", &l, &r); printf("%lld\n", seg.query(l, r)); }
	}
	return 0;
}