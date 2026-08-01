#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;

int n, m, Q;
struct Operation { int t, l, r, v; } a[N];
struct Query { int l, r; } q[N];

struct SegmentTree {
	LL t[N << 2], lazy[N << 2];
	void setlazy(int x, LL v, int len) { t[x] = v * len, lazy[x] = v; }
	void lazydown(int x, int l, int r, int mid) { if(lazy[x] != -1) setlazy(x << 1, lazy[x], mid - l + 1), setlazy(x << 1 | 1, lazy[x], r - mid), lazy[x] = -1; }
	void build(int x = 1, int l = 1, int r = n) {
		t[x] = 0, lazy[x] = -1;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) { setlazy(x, qv, r - l + 1); return; }
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = t[x << 1] + t[x << 1 | 1];
	}
	LL query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return query(ql, qr, x << 1, l, mid) + query(ql, qr, x << 1 | 1, mid + 1, r);
	}
} seg;

namespace Subtask12 {
	void main() {
		for(int i = 1; i <= Q; i++) {
			LL ans = 0;
			seg.build();
			for(int j = q[i].l; j <= q[i].r; j++) {
				if(a[j].t == 1) seg.modify(a[j].l, a[j].r, a[j].v);
				else ans += seg.query(a[j].l, a[j].r);
			}
			printf("%lld\n", ans);
		}
	}
}

namespace Subtask3 {
	bool check() {
		for(int i = 1; i <= m; i++) if(a[i].t == 1) return false;
		return true;
	}
	void main() {
		while(Q--) puts("0");
	}
}

namespace Subtask4 {
	bool check() {
		for(int i = 1; i <= Q; i++) if(q[i].l != 1) return false;
		return true;
	}
	LL out[N];
	void main() {
		for(int i = 1; i <= m; i++) {
			if(a[i].t == 1) seg.modify(a[i].l, a[i].r, a[i].v), out[i] = out[i - 1];
			else out[i] = out[i - 1] + seg.query(a[i].l, a[i].r);
		}
		for(int i = 1; i <= Q; i++) printf("%lld\n", out[q[i].r]);
	}
}

int main() {
#ifndef DEBUG
	freopen("mfsn.in", "r", stdin);
	freopen("mfsn.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= m; i++) { scanf("%d%d%d", &a[i].t, &a[i].l, &a[i].r); if(a[i].t == 1) scanf("%d", &a[i].v); }
	for(int i = 1; i <= Q; i++) scanf("%d%d", &q[i].l, &q[i].r);
	if(std::max({n, m, Q}) <= 5000) Subtask12::main();
	else if(Subtask3::check()) Subtask3::main();
	else if(Subtask4::check()) Subtask4::main();
	return 0;
}