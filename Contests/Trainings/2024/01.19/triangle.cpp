#include <bits/stdc++.h>

#ifndef DEBUG
	#undef assert
	#define assert(...) ((void)0)
#endif

typedef long long LL;

const int N = 2e5 + 5;

int n, Q;
LL a[N];

struct SegValue {
	LL pre, suf, match;
};
SegValue calc(const SegValue &x, const SegValue &y) {
	SegValue z;
	LL val = std::min(x.suf, y.pre);
	z.match = x.match + y.match + val;
	z.pre = x.pre + (y.pre - val);
	z.suf = (x.suf - val) + y.suf;
	return z;
}
struct SegmentTree {
	SegValue t[N << 4];
	void modify(int qind, const SegValue &qv, int x = 1, int l = 1, int r = 4 * n) {
		if(l == r) { t[x] = qv; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	SegValue query() { return t[1]; }
} seg;

int main() {
#ifndef DEBUG
	freopen("triangle.in", "r", stdin);
	freopen("triangle.out", "w", stdout);
#endif
	scanf("%d%d", &n, &Q);
	LL even = 0;
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		if(a[i] & 1) seg.modify(2 * i - 1, {0, 1, 0});
		seg.modify(4 * i - 2, {a[i] >> 1, 0, 0}), even += a[i] >> 1;
	}
	while(Q--) {
		int p, x;
		scanf("%d%d", &p, &x);
		even -= a[p] >> 1;
		a[p] += x;
		even += a[p] >> 1;
		seg.modify(2 * p - 1, {0, a[p] & 1, 0});
		seg.modify(4 * p - 2, {a[p] >> 1, 0, 0});
		LL match = seg.query().match;
		// printf("match = %lld, even = %lld\n", match, even);
		printf("%lld\n", match + (even * 2 - 2 * match) / 3);
		// printf("a = %lld\n", a[1]);
	}
	return 0;
} /*
4 3
3 1 4 1
3 -3
1 6
2 1
*/