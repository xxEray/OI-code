#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, K;
LL A;
struct Node { int x, y; LL c; } a[N];

LL f[N], s[N];

struct SegmentTree {
	LL t[N << 2], lazy[N << 2];
	void setlazy(int x, LL v) { t[x] += v, lazy[x] += v; }
	void lazydown(int x) { setlazy(x << 1, lazy[x]), setlazy(x << 1 | 1, lazy[x]), lazy[x] = 0; }
	void set(int qind, LL qv, int x = 1, int l = 0, int r = K + 1) {
		if(l == r) { t[x] = qv, lazy[x] = 0; return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qind <= mid) set(qind, qv, x << 1, l, mid);
		else set(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]);
	}
	void add(int ql, int qr, LL qv, int x = 1, int l = 0, int r = K + 1) {
		if(ql <= l && r <= qr) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]);
	}
	LL query(int ql, int qr, int x = 1, int l = 0, int r = K + 1) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::min(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int main() {
	scanf("%d%d%lld", &n, &K, &A);
	for(int i = 1; i <= n; i++) scanf("%d%d%lld", &a[i].x, &a[i].y, &a[i].c);
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.x > y.x; });
	f[K + 1] = 0;
	for(int i = 1; i <= n; i++) f[K + 1] += a[i].c;
	seg.set(K + 1, f[K + 1] + K * A - s[0]);
	for(int i = K, j = 1; i >= 0; i--) {
		while(j <= n && a[j].x == i) {
			s[a[j].y] += a[j].c;
			seg.add(K - a[j].y + 1, K + 1, -a[j].c);
			j++;
		}
		f[i] = seg.query(i + 1, K + 1) - i * A;
		seg.set(i, f[i] + (i - 1) * A - s[K - i + 1]);
		// printf("f[%d] = %lld\n", i, f[i]);
	}
	printf("%lld\n", f[0]);
	return 0;
}