#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int al[N], ar[N];

struct SegmentTree {
	int t[N << 2], lz[N << 2];
	void setlazy(int x, int v) { t[x] += v, lz[x] += v; }
	void lazydown(int x) { setlazy(x << 1, lz[x]), setlazy(x << 1 | 1, lz[x]), lz[x] = 0; }
	void build(int x = 1, int l = 0, int r = m + 1) {
		t[x] = 0, lz[x] = 0;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int ql, int qr, int qv, int x = 1, int l = 0, int r = m + 1) {
		if(ql > qr) return;
		if(ql <= l && r <= qr) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]);
	}
	int query(int ql, int qr, int x = 1, int l = 0, int r = m + 1) {
		if(ql > qr) return INF;
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::min(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

std::vector<int> vct[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d%d", &al[i], &ar[i]);
	for(int i = 1; i <= n; i++) if(ar[i] == al[i] + 1) al[i] = m + 1, ar[i] = 0;
	for(int i = 1; i <= n; i++) vct[al[i]].emplace_back(ar[i]);
	seg.build();
	for(int i = 1; i <= m; i++) seg.modify(1, i, 1);
	int mn = 0;
	for(int i = 0; i <= m + 1; i++) {
		for(auto j : vct[i]) seg.modify(1, j, -1);
		if(i) seg.modify(i + 1, m + 1, 1);
		mn = std::min(mn, seg.query(i + 1, m + 1));
		// printf("seg(i = %d): ", i); for(int j = 0; j <= m + 1; j++) printf("%d ", seg.query(j, j)); puts("");
	}
	printf("%d\n", std::max(n - m, -mn));
	return 0;
} /*
4 4
0 3
2 3
1 3
3 4
*/