#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, m, K;
int a[N], b[N], bi[N];
struct Node { int l, r, c, d, di; } nd[N];
struct Query { int c, d, id, t, di; };
std::vector<Query> q[N];

int tmp[N * 2];
void discrete() {
	for(int i = 1; i <= n; i++) tmp[++K] = b[i];
	for(int i = 1; i <= m; i++) tmp[++K] = nd[i].d;
	std::sort(tmp + 1, tmp + K + 1);
	K = std::unique(tmp + 1, tmp + K + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) bi[i] = std::lower_bound(tmp + 1, tmp + K + 1, b[i]) - tmp;
	for(int i = 1; i <= m; i++) nd[i].di = std::lower_bound(tmp + 1, tmp + K + 1, nd[i].d) - tmp;
}

struct Trie {
	int c[N * 50][2], val[N * 50], sz[N * 50];
	int tot;
	void init() { c[1][0] = c[1][1] = val[1] = sz[1] = 0; tot = 1; }
	int nw() { tot++; c[tot][0] = c[tot][1] = val[tot] = sz[tot] = 0; return tot; }
	void insert(int x, int y) {
		int now = 1;
		for(int i = 24; i >= 0; i--) {
			sz[now]++;
			if(y >> i & 1) {
				if(!c[now][~(x ^ y) >> i & 1]) c[now][~(x ^ y) >> i & 1] = nw();
				val[c[now][~(x ^ y) >> i & 1]]++;
			}
			if(!c[now][(x ^ y) >> i & 1]) c[now][(x ^ y) >> i & 1] = nw();
			now = c[now][(x ^ y) >> i & 1];
		}
		sz[now]++, val[now]++;
		val[0] = 0;
	}
	int query(int x, int y) {
		val[0] = 0;
		int ans = 0, now = 1;
		for(int i = 24; i >= 0; i--) {
			ans += val[now];
			if(y >> i & 1) ans += sz[c[now][x >> i & 1]], now = c[now][~x >> i & 1];
			else now = c[now][x >> i & 1];
		}
		return ans + val[now];
	}
} trie;
int out[N];
struct Operation { int type, v1, v2, id; };
struct SegmentTree {
	std::vector<Operation> t[N << 3];
	void insert(int qind, const Operation &qv, int x = 1, int l = 1, int r = K) {
		t[x].push_back(qv);
		if(l == r) return;
		int mid = (l + r) >> 1;
		if(qind <= mid) insert(qind, qv, x << 1, l, mid);
		else insert(qind, qv, x << 1 | 1, mid + 1, r);
	}
	void query(int ql, int qr, const Operation &qv, int x = 1, int l = 1, int r = K) {
		if(ql <= l && r <= qr) { t[x].push_back(qv); return; }
		int mid = (l + r) >> 1;
		if(ql <= mid) query(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) query(ql, qr, qv, x << 1 | 1, mid + 1, r);
	}
	void solve(int x = 1, int l = 1, int r = K) {
		trie.init();
		for(auto &p : t[x])
			if(p.type == 0) trie.insert(p.v1, p.v2);
			else out[p.id] += p.type * trie.query(p.v1, p.v2);
		if(l == r) return;
		int mid = (l + r) >> 1;
		solve(x << 1, l, mid), solve(x << 1 | 1, mid + 1, r);
	}
} seg1, seg2;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);
	for(int i = 1; i <= m; i++) scanf("%d%d%d%d", &nd[i].l, &nd[i].r, &nd[i].c, &nd[i].d);
	discrete();
	for(int i = 1; i <= m; i++) {
		int l = nd[i].l, r = nd[i].r, c = nd[i].c, d = nd[i].d, di = nd[i].di;
		q[l - 1].push_back({c, d, i, -1, di}), q[r].push_back({c, d, i, 1, di});
	}
	for(int i = 1; i <= n; i++) {
		seg1.insert(bi[i], {0, a[i], b[i], 0}), seg2.insert(bi[i], {0, a[i], 0, 0});
		for(auto p : q[i]) {
			seg1.query(1, p.di, {p.t, p.c, 0, p.id});
			seg2.query(p.di + 1, K, {p.t, p.c, p.d, p.id});
		}
	}
	seg1.solve(), seg2.solve();
	for(int i = 1; i <= m; i++) printf("%d\n", out[i]);
	return 0;
} /*
2 1
1 4
2 3
1 2 3 5
*/