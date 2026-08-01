#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n, m;
int a[N];

struct SegementTree {
	int t[N << 2];
	void modify(int qind, int qv, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] = qv; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		assert(ql <= qr);
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::max(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int sum[N];
std::vector<int> vct[N], dot[2][N];

struct Query { int l, r, id; } q[N];
int out[N];

struct BIT {
	int t[N];
	void add(int x, int v) { assert(1 <= x && x <= n); while(x <= n) t[x] += v, x += x & -x; }
	int query(int r) { assert(1 <= r && r <= n); int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
} bit;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), vct[a[i]].push_back(i);
	for(int i = 1; i <= m; i++) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	for(int o = 1; o <= n; o++) {
		int sz = vct[o].size();
		sum[o] = sum[o - 1] + sz;
		for(int i = 0; i < sz - 1; i++) {
			int mx = seg.query(vct[o][i], vct[o][i + 1]);
			dot[1][o].push_back(o), dot[0][mx].push_back(o);
		}
		for(int x : vct[o]) seg.modify(x, o);
	}
	std::sort(q + 1, q + m + 1, [&](Query x, Query y) { return x.l > y.l; });
	for(int i = n, j = 1; i >= 1; i--) {
		for(int x : dot[0][i]) bit.add(x, -1);
		for(int x : dot[1][i]) bit.add(x, 1);
		while(j <= m && q[j].l == i) out[q[j].id] = sum[q[j].r] - sum[q[j].l - 1] - bit.query(q[j].r), j++;
	}
	for(int i = 1; i <= m; i++) printf("%d\n", out[i]);
	return 0;
}