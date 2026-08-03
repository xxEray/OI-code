#include <bits/stdc++.h>

const int N = 1e6 + 5;
const int INF = 0x3f3f3f3f;

int n, Q;
int a[N];

struct SegmentTree {
	int BD;
	struct Node { int mn, mx, sorted; } t[2 * (1 << 20) + 5];
	Node calc(const Node &x, const Node &y, int cost) {
		Node z = {std::min(x.mn, y.mn), std::max(x.mx, y.mx), 0};
		if(x.mx <= y.mn) z.sorted = std::max(x.sorted, y.sorted);
		else z.sorted = cost;
		return z;
	}
	void build() {
		for(BD = 1; BD < n; BD <<= 1);
		for(int i = BD; i < BD + n; i++) t[i] = {a[i - BD], a[i - BD], 0};
		for(int i = BD + n; i < 2 * BD; i++) t[i] = {INF, INF, 0};
		for(int j = BD >> 1; j; j >>= 1)
			for(int i = j; i < 2 * j; i++)
				t[i] = calc(t[i << 1], t[i << 1 | 1], BD / j >> 1);
	}
	void modify(int x, int v) {
		x += BD, t[x] = {v, v, 0}, x >>= 1;
		for(int d = 1; x; d <<= 1) {
			t[x] = calc(t[x << 1], t[x << 1 | 1], d);
			x >>= 1;
		}
	}
	int query() { return t[1].sorted; }
} seg;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &Q);
		for(int i = 0; i < n; i++) scanf("%d", &a[i]);
		seg.build();
		printf("%d\n", seg.query());
		while(Q--) {
			int x, v;
			scanf("%d%d", &x, &v);
			seg.modify(x, v);
			printf("%d\n", seg.query());
		}
	}
	return 0;
} /*
3
2 0
1 2
2 1
1000000000 999999999
1 1000000000
6 2
2 5 3 4 1 6
1 2
4 5
*/