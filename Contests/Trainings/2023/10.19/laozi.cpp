#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
char s[N];
LL wi[30], wc, we;

int z[N];
void z_algorithm() {
	int zl = 0, zr = 0;
	for(int i = 2; i <= n; i++) {
		if(i <= zr) z[i] = std::min(zr - i + 1, z[i - zl + 1]);
		while(i + z[i] <= n && s[i + z[i]] == s[1 + z[i]]) z[i]++;
		if(i + z[i] - 1 > zr) zl = i, zr = i + z[i] - 1;
	}
}

struct SegmentTree {
	LL t[N << 2], lazy[N << 2];
	void setlazy(int x, LL v, int l, int r) { t[x] = std::min(t[x], v - r * we), lazy[x] = std::min(lazy[x], v); }
	void lazydown(int x, int l, int r, int mid) {
		setlazy(x << 1, lazy[x], l, mid);
		setlazy(x << 1 | 1, lazy[x], mid + 1, r);
		lazy[x] = LLINF;
	}
	void build(int x = 1, int l = 1, int r = n) {
		t[x] = lazy[x] = LLINF;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
//		if(x == 1) printf("modify [%d, %d] %lld\n", ql, qr, qv);
		if(ql <= l && r <= qr) { setlazy(x, qv, l, r); return; }
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]);
	}
	LL query(int qind, int x = 1, int l = 1, int r = n) {
//		if(x == 1) printf("query %d\n", qind);
		if(l == r) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(qind <= mid) return query(qind, x << 1, l, mid);
		else return query(qind, x << 1 | 1, mid + 1, r);
	}
} seg;

int main() {
#ifndef DEBUG
	freopen("laozi.in", "r", stdin);
	freopen("laozi.out", "w", stdout);
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++) s[i] = s[i] - 'a' + 1;
	for(int i = 1; i <= 26; i++) scanf("%lld", &wi[i]);
	scanf("%lld%lld", &wc, &we);
	z_algorithm();
	seg.build();
	seg.modify(1, 1, wi[s[1]] + we);
	for(int i = 1; i < n; i++) {
		LL f = seg.query(i);
//		printf("f[%d] = %lld\n", i, f);
		int r = std::min({n, 2 * i, i + 1 + z[i + 1] - 1});
		if(r >= i + 1) seg.modify(i + 1, r, f + wc + (2 * i) * we);
		seg.modify(i + 1, i + 1, f + wi[s[i + 1]] + (i + 1) * we);
	}
	printf("%lld\n", seg.query(n));
	return 0;
}
