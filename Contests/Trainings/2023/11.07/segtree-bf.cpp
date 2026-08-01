#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

int n, m;

struct SegmentTree {
	LL t[N << 2], lazy[N << 2];
	void setlazy(int x, LL v) { t[x] += v, lazy[x] += v; }
	void lazydown(int x) { setlazy(x << 1, lazy[x]), setlazy(x << 1 | 1, lazy[x]), lazy[x] = 0; }
	void add(int ql, int qr, LL qv, int x = 1, int l = 0, int r = n - 1) {
		if(ql <= l && r <= qr) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]);
	}
	LL query(int ql, int qr, int x = 1, int l = 0, int r = n - 1) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::min(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

unsigned long long Seed;
long long W, X, Y, Z;
unsigned long long HRAND() {
	Seed ^= Seed << 9;
	Seed ^= Seed >> 11;
	Seed ^= Seed << 15;
	return Seed;
}
void Gen(int &op, int &k) {
	long long OP = HRAND() % (X + Y + 2 * Z);
	if(OP < X) op = 1 + HRAND() % 2, k = 0;
	else if(OP < X + Y) op = 3 + HRAND() % 2, k = HRAND() % (2 * W) - W;
	else if(OP < X + Y + Z) op = 5 + HRAND() % 2, k = 0;
	else op = 7 + HRAND() % 2, k = 0;
}

int main() {
	scanf("%d%d", &n, &m);
	scanf("%llu%lld%lld%lld%lld", &Seed, &W, &X, &Y, &Z);
	long long ans = 0;
	int x = 0, y = n - 2;
	for(int q = 1; q <= m; q++) {
		int op, k;
		Gen(op, k);
		// printf("op = %d, k = %d\n", op, k);
		if(op == 1) x = (x + 1 == y ? 0 : x + 1);
		else if(op == 2) y = (y - 1 == x ? n - 1 : y - 1);
		else if(op == 3) seg.add(0, x, k);
		else if(op == 4) seg.add(0, y, k);
		else if(op == 5) ans ^= (LL)(q % 998) * (seg.query(0, x) + (LL)5e14);
		else if(op == 6) ans ^= (LL)(q % 998) * (seg.query(0, y) + (LL)5e14);
		else if(op == 7) ans ^= (LL)(q % 998) * (seg.query(x + 1, n - 1) + (LL)5e14);
		else if(op == 8) ans ^= (LL)(q % 998) * (seg.query(y + 1, n - 1) + (LL)5e14);
	}
	printf("%lld\n", ans);
	return 0;
}