#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;

int n, Q;
LL a[N];

LL gcd(LL x, LL y) { return y == 0 ? std::abs(x) : gcd(y, x % y); }

struct SegmentTreeGcd {
	LL t[N << 2];
	void modify(int qind, LL qv, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] += qv; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = gcd(t[x << 1], t[x << 1 | 1]);
	}
	LL query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return gcd(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} segg;

struct BIT {
	LL t[N];
	void add(int x, LL v) { while(x <= n) t[x] += v, x += x & -x; }
	LL query(int x) { LL ret = 0; while(x) ret += t[x], x -= x & -x; return ret; }
	void add(int l, int r, LL v) { add(l, v), add(r + 1, -v); }
} segv;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	n++;
	for(int i = 1; i <= n; i++) segv.add(i, i, a[i]), segg.modify(i, a[i] - a[i - 1]);
	while(Q--) {
		char s[2];
		int l, r;
		LL d;
		scanf("%s", s);
		if(s[0] == 'C') scanf("%d%d%lld", &l, &r, &d), segv.add(l, r, d), segg.modify(l, d), segg.modify(r + 1, -d);
		else if(s[0] == 'Q') scanf("%d%d", &l, &r), printf("%lld\n", l == r ? segv.query(l) : gcd(segv.query(l), segg.query(l + 1, r)));
	}
	return 0;
}