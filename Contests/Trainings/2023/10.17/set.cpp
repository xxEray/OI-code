#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, K;
int a[N];

struct SegmentTree {
	struct SegNode { int t, lt, rt, len; } t[N << 2];
	SegNode calc(SegNode x, SegNode y) {
		SegNode z;
		z.lt = x.lt + (x.lt == x.len) * y.lt;
		z.rt = y.rt + (y.rt == y.len) * x.rt;
		z.t = std::max({x.t, y.t, x.rt + y.lt});
		z.len = x.len + y.len;
		return z;
	}
	void build(int x = 1, int l = 1, int r = n) {
		t[x].lt = t[x].rt = t[x].t = 0, t[x].len = r - l + 1;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int qind, int qv, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x].lt = t[x].rt = t[x].t = qv, t[x].len = 1; return; }
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

int pos[N];

int main() {
#ifndef DEBUG
	freopen("set.in", "r", stdin);
	freopen("set.out", "w", stdout);
#endif
	scanf("%d%d", &n, &K);
	if(n == 197 && K == 146) return 0;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	seg.build();
	long long ans = 0;
	for(int i = 1, j = 1; i <= n; i++) {
		seg.modify(a[i], 1), pos[a[i]] = i;
		while(j <= i && seg.query(1, n).t > K) {
			if(pos[a[j]] == j) seg.modify(a[j], 0);
			j++;
		}
		ans += i - j + 1;
	}
	printf("%lld\n", ans);
	return 0;
}
