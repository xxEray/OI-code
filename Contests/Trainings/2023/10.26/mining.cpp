#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int *a[N];

struct SegmentTree {
	struct SegValue { int mn, cnt; };
	SegValue t[N << 2];
	int lazy[N << 2];
	SegValue calc(const SegValue &x, const SegValue &y) {
		SegValue z;
		z.mn = std::min(x.mn, y.mn);
		z.cnt = (z.mn == x.mn) * x.cnt + (z.mn == y.mn) * y.cnt;
		return z;
	}
	void build(int x = 1, int l = 1, int r = n * m) {
		t[x] = {0, 1}, lazy[x] = 0;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void setlazy(int x, int v) { t[x].mn += v, lazy[x] += v; }
	void lazydown(int x) { setlazy(x << 1, lazy[x]), setlazy(x << 1 | 1, lazy[x]), lazy[x] = 0; }
	void modify(int qind, int qv, int x = 1, int l = 1, int r = n * m) {
		if(l == r) { t[x] = {qv, 1}, lazy[x] = INF; return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	void add(int ql, int qr, int qv, int x = 1, int l = 1, int r = n * m) {
		if(ql > qr) return;
		assert(1 <= ql && ql <= qr && qr <= n * m);
		// printf("add %d %d %d %d %d %d\n", ql, qr, qv, x, l, r);
		if(ql <= l && r <= qr) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	SegValue query(int ql, int qr, int x = 1, int l = 1, int r = n * m) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

std::pair<int, int> pos[N];

int min(int x, int y, int z) {
	if(x > y) std::swap(x, y);
	if(x > z) std::swap(x, z);
	return x;
}
int max(int x, int y, int z) {
	if(x < y) std::swap(x, y);
	if(x < z) std::swap(x, z);
	return x;
}
int middle(int x, int y, int z) {
	if(x > y) std::swap(x, y);
	if(x > z) std::swap(x, z);
	if(y > z) std::swap(y, z);
	return y;
}

int main() {
#ifndef DEBUG
	freopen("mining.in", "r", stdin);
	freopen("mining.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	a[0] = new int[m + 6](), a[n + 1] = new int[m + 6]();
	for(int i = 1; i <= n; i++) {
		a[i] = new int[m + 6]();
		for(int j = 1; j <= m; j++) { int x; scanf("%d", &x); pos[x] = {i, j}; }
	}
	seg.build();
	long long ans = 0;
	for(int i = 1; i <= n * m; i++) {
		const auto &[x, y] = pos[i];
		a[x][y] = i;
		for(int dx : {-1, 1}) for(int dy : {-1, 1}) {
			#define all a[x + dx][y], a[x][y + dy], a[x + dx][y + dy]
			seg.add(max(all) + 1, i, 1);
			seg.add(min(all) + 1, middle(all), 1);
			seg.add(middle(all) + 1, max(all), -1);
			seg.add(1, min(all), -1);
		}
		// printf("i = %d: ", i); for(int j = 1; j <= i; j++) printf("%d ", seg.query(j, j).mn); puts("");
		const auto &[v, cnt] = seg.query(1, i);
		if(v == 4) ans += cnt;
	}
	printf("%lld\n", ans);
	return 0;
} /*
4 4
4 1 5 6
3 13 7 11
2 14 8 9
16 15 12 10
*/