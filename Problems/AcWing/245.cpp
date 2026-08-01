#include <bits/stdc++.h>

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int n, Q;

struct Node { int sum, suml, sumr, ans; };
Node calc(Node x, Node y) {
	Node z;
	z.sum = x.sum + y.sum;
	z.suml = std::max(x.suml, x.sum + y.suml);
	z.sumr = std::max(y.sumr, y.sum + x.sumr);
	z.ans = std::max({x.ans, y.ans, x.sumr, y.suml, x.sumr + y.suml});
	return z;
}
struct SegmentTree {
	Node t[N << 2];
	void modify(int qind, int qv, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] = {qv, qv, qv, qv}; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	Node query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); seg.modify(i, x); }
	while(Q--) {
		int t, x, y;
		scanf("%d%d%d", &t, &x, &y);
		if(t == 1) printf("%d\n", seg.query(std::min(x, y), std::max(x, y)).ans);
		else seg.modify(x, y);
	}
	return 0;
}