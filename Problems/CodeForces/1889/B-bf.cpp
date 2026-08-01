#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
LL c;
LL a[N];

struct SegmentTree {
	struct NodeValue { LL mx; int pos; };
	struct SegNode { NodeValue v; LL lazy; } t[N << 2];
	NodeValue calc(const NodeValue &x, const NodeValue &y) {
		NodeValue z;
		z.mx = std::max(x.mx, y.mx);
		if(z.mx == x.mx) z.pos = x.pos;
		else z.pos = y.pos;
		return z;
	}
	void build(int x = 1, int l = 1, int r = n) {
		for(int i = 1; i <= n; i++) t[i].v = {-LLINF, i};
	}
	void modify(int qind, LL qv, int x = 1, int l = 1, int r = n) {
		t[qind].v.mx = qv;
	}
	void add(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		for(int i = ql; i <= qr; i++) t[i].v.mx += qv * i;
	}
	NodeValue query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		NodeValue ans = {-LLINF * 2, 0}; for(int i = ql; i <= qr; i++) ans = calc(ans, t[i].v); return ans;
	}
} seg;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%lld", &n, &c);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		seg.build();
		for(int i = n; i >= 1; i--) {
			if(i + 1 <= n) seg.add(i + 1, n, c);
			while(true) {
				if(i + 1 > n) break;
				auto [mx, pos] = seg.query(i + 1, n);
				printf("query [%d, %d] = %lld,%d\n", i + 1, n, mx, pos);
				if(mx < -LLINF / 2 || mx < -a[i]) break;
				a[i] += a[pos], seg.modify(pos, -LLINF);
			}
			seg.modify(i, a[i] - i * c * i);
			printf("%d: ", i); for(int j = i; j <= n; j++) printf("%lld ", seg.query(j, j).mx); puts("");
		}
		seg.modify(1, -LLINF);
		puts(seg.query(1, n).mx < -LLINF / 2 ? "Yes" : "No");
	}
	return 0;
}