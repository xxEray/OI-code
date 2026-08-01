#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, K;
int a[N];

struct SegmentTree {
	struct SegNode { int mn, mx; } t[N << 2];
	SegNode calc(SegNode x, SegNode y) {
		SegNode z;
		z.mn = std::min(x.mn, y.mn);
		z.mx = std::max(x.mx, y.mx);
		return z;
	}
	void modify(int qind, int qv, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x].mn = t[x].mx = qv; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	SegNode query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int b[N];

int main() {
#ifndef DEBUG
	freopen("set.in", "r", stdin);
	freopen("set.out", "w", stdout);
#endif
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) seg.modify(a[i], i);
	for(int i = 1; i <= n - K; i++) {
		const auto &[l, r] = seg.query(i, i + K);
		b[r] = std::max(b[r], l);
//		printf("[%d, %d]\n", l, r);
	}
	int mxr = 0;
	long long ans = 0;
	for(int i = 1; i <= n; i++) mxr = std::max(mxr, b[i]), ans += i - mxr;
	printf("%lld\n", ans);
	return 0;
}
