#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int M = 4e5 + 5;
const LL MOD = 1e9 + 7;

int n, m;
std::pair<int, int> e[M];

int ld[N * 2];
int find(int x) { return x == ld[x] ? x : ld[x] = find(ld[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? ld[x] = y : 0; }

int son[N * 2][2], fa[N * 2];
int dfn[N * 2], sz[N * 2], time_stamp = 1;
void dfs(int u) {
	if(u > n) dfn[u] = time_stamp, sz[u] = 0;
	else dfn[u] = time_stamp++, sz[u] = 1;
	for(int v : son[u]) if(v) {
		dfs(v);
		sz[u] += sz[v];
	}
}

LL power10[N];

struct SegmentTree {
	LL t[N << 2], pls[N << 2], mul[N << 2];
	void pushpls(int x, LL v) {
		(t[x] += v) %= MOD;
		(pls[x] += v) %= MOD;
	}
	void pushmul(int x, LL v) {
		(t[x] *= v) %= MOD;
		(pls[x] *= v) %= MOD;
		(mul[x] *= v) %= MOD;
	}
	void pushdown(int x) {
		pushmul(x << 1, mul[x]), pushmul(x << 1 | 1, mul[x]), mul[x] = 1;
		pushpls(x << 1, pls[x]), pushpls(x << 1 | 1, pls[x]), pls[x] = 0;
	}
	void build(int x = 1, int l = 1, int r = n) {
		t[x] = 0, pls[x] = 0, mul[x] = 1;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void multiply(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) { pushmul(x, qv); return; }
		int mid = (l + r) >> 1;
		pushdown(x);
		if(ql <= mid) multiply(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) multiply(ql, qr, qv, x << 1 | 1, mid + 1, r);
	}
	void add(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) { pushpls(x, qv); return; }
		int mid = (l + r) >> 1;
		pushdown(x);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
	}
	LL query(int qind, int x = 1, int l = 1, int r = n) {
		if(l == r) return t[x];
		int mid = (l + r) >> 1;
		pushdown(x);
		if(qind <= mid) return query(qind, x << 1, l, mid);
		else return query(qind, x << 1 | 1, mid + 1, r);
	}
} seg;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%d%d", &e[i].first, &e[i].second);
	for(int i = 1; i <= n * 2; i++) ld[i] = i;
	int cn = n;
	for(int i = 1; i <= m; i++) {
		auto [u, v] = e[i];
		if(find(u) == find(v)) continue;
		cn++;
		u = find(u), v = find(v);
		fa[u] = fa[v] = cn, son[cn][0] = u, son[cn][1] = v;
		merge(u, cn), merge(v, cn);
	}
	dfs(cn);
	seg.build();
	// for(int i = 1; i <= cn; i++) printf("%d: son=%d %d, fa=%d, dfn=%d, sz=%d\n", i, son[i][0], son[i][1], fa[i], dfn[i], sz[i]);
	for(int i = 1; i <= n * 2; i++) ld[i] = i;
	power10[0] = 1;
	for(int i = 1; i <= n; i++) power10[i] = power10[i - 1] * 10 % MOD;
	for(int i = 1; i <= m; i++) {
		auto [u, v] = e[i];
		if(find(u) == find(v)) continue;
		int fu = find(u), fv = find(v);
		LL vu = seg.query(dfn[u]), vv = seg.query(dfn[v]);
		// printf("u = %d, fu = %d, vu = %lld\n", u, fu, vu);
		// printf("v = %d, fv = %d, vv = %lld\n", v, fv, vv);
		seg.multiply(dfn[fu], dfn[fu] + sz[fu] - 1, power10[sz[fv]]);
		seg.add(dfn[fu], dfn[fu] + sz[fu] - 1, (power10[sz[fv] - 1] * i + vv) % MOD);
		seg.multiply(dfn[fv], dfn[fv] + sz[fv] - 1, power10[sz[fu]]);
		seg.add(dfn[fv], dfn[fv] + sz[fv] - 1, (power10[sz[fu] - 1] * i + vu) % MOD);
		merge(fu, fa[fu]), merge(fv, fa[fv]);
	}
	for(int i = 1; i <= n; i++) printf("%lld\n", seg.query(dfn[i]));
	return 0;
}