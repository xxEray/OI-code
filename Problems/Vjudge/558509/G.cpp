#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, Q;
int a[N][3];
struct Node { int l, r; LL w; } b[N];
LL cl[N], cr[N], c[N];

LL f[N];

struct SegmentTree1 {
	LL t[N << 2], lazy[N << 2];
	void build(int x = 1, int l = 1, int r = n) {
		for(int i = 1; i <= n; i++) t[i] = -LLINF;
	}
	void modify(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		for(int i = ql; i <= qr; i++) t[i] = std::max(t[i], qv);
	}
	LL query(int qind, int x = 1, int l = 1, int r = n) {
		return t[qind];
	}
} seg1;

struct SegmentTree2 {
	LL t[N << 2], p[N << 2], lazy[N << 2];
	void build(int x = 1, int l = 1, int r = n) {
		for(int i = 1; i <= n; i++) p[i] = cl[i] - c[i - 1], t[i] = -LLINF;
	}
	void modify(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		for(int i = ql; i <= qr; i++) t[i] = std::max(t[i], qv + p[i]);
	}
	LL query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		LL ret = -LLINF; for(int i = ql; i <= qr; i++) ret = std::max(ret, t[i]); return ret;
	}
} seg2;

int main() {
	scanf("%d%d", &n, &Q);
	for(int j = 0; j < 3; j++) for(int i = 1; i <= n; i++) scanf("%d", &a[i][j]);
	for(int i = 1; i <= Q; i++) scanf("%d%d%lld", &b[i].l, &b[i].r, &b[i].w);
	std::sort(b + 1, b + Q + 1, [&](Node x, Node y) { return x.l < y.l; });
	for(int i = 1; i <= n; i++) cl[i] = cl[i - 1] + a[i][0];
	for(int i = n; i >= 1; i--) cr[i] = cr[i + 1] + a[i][2];
	for(int i = 1; i <= n; i++) c[i] = c[i - 1] + a[i][1];
	printf("cl: "); for(int i = 1; i <= n; i++) printf("%lld ", cl[i]); puts("");
	printf(" c: "); for(int i = 1; i <= n; i++) printf("%lld ", c[i]); puts("");
	printf("cr: "); for(int i = 1; i <= n; i++) printf("%lld ", cr[i]); puts("");
	seg1.build(), seg2.build();
	for(int i = 1; i <= Q; i++) seg2.modify(b[i].l, b[i].r, -b[i].w);
	printf("seg2.query: "); for(int i = 1; i <= n; i++) printf("%lld ", seg2.query(i, i)); puts("");
	f[0] = -LLINF;
	for(int i = 1, j = 1; i <= n; i++) {
		while(j <= Q && b[j].l == i) seg1.modify(i, b[j].r, f[i - 1] - c[i - 1] - b[i].w), j++;
		f[i] = std::max(seg1.query(i), seg2.query(1, i)) + c[i];
		printf("f[%d] = %lld (%lld %lld)\n", i, f[i], seg1.query(i) + c[i], seg2.query(1, i) + c[i]);
	}
	LL ans = -LLINF;
	for(int i = 1; i <= n; i++) ans = std::max(ans, f[i] + cr[i]);
	printf("%lld\n", ans);
	return 0;
}