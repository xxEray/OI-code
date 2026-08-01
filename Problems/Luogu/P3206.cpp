#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int M = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m, K;
int eu[M], ev[M], ew[M], last[M];

struct LCT {
	int c[N + M][2], fa[N + M], v[N + M], s[N + M];
	int stk[N + M];
	bool r[N + M];
	int maxind(int x, int y) { return v[x] > v[y] ? x : y; }
	int maxind(int x, int y, int z) { return maxind(x, maxind(y, z)); }
	int chtype(int x) { return x == c[fa[x]][1]; }
	void pushup(int x) { s[x] = maxind(x, s[c[x][0]], s[c[x][1]]); }
	void pushr(int x) { if(x) r[x] ^= 1, std::swap(c[x][0], c[x][1]); }
	void pushdown(int x) { if(r[x]) pushr(c[x][0]), pushr(c[x][1]), r[x] = 0; }
	bool nroot(int x) { return c[fa[x]][0] == x || c[fa[x]][1] == x; }
	void rotate(int x) {
		int y = fa[x], z = fa[y], t = chtype(x), ty = chtype(y);
		c[y][t] = c[x][!t]; if(c[x][!t]) fa[c[x][!t]] = y;
		fa[x] = z; if(nroot(y)) c[z][ty] = x;
		c[x][!t] = y, fa[y] = x;
		pushup(y), pushup(x);
	}
	void splay(int x) {
		int y = x, top = 0;
		stk[++top] = y;
		while(nroot(y)) stk[++top] = y = fa[y];
		while(top) pushdown(stk[top--]);
		for(; nroot(x); rotate(x)) if(nroot(fa[x])) rotate(chtype(x) == chtype(fa[x]) ? fa[x] : x);
	}
	void access(int x) { for(int y = 0; x; y = x, x = fa[x]) splay(x), c[x][1] = y, pushup(x); }
	void makeroot(int x) { access(x), splay(x), pushr(x); }
	int findroot(int x) {
		access(x), splay(x);
		while(c[x][0]) pushdown(x), x = c[x][0];
		splay(x);
		return x;
	}
	void split(int x, int y) { makeroot(x), access(y), splay(y); }
	void link(int x, int y) { makeroot(x); if(findroot(y) != x) fa[x] = y; }
	void cut(int x, int y) {
		makeroot(x);
		if(findroot(y) == x && fa[y] == x && !c[y][0]) fa[y] = c[x][1] = 0, pushup(x);
	}
	void modify(int x, int val) { splay(x), v[x] = val, s[x] = x, pushup(x); }
} lct;

int cu[M], cv[M];
struct Edge { int u, v, w, id; };
std::vector<Edge> t[M << 2];
void insert(int ql, int qr, Edge qv, int x = 1, int l = 0, int r = K) {
	// if(x == 1) printf("insert [%d, %d] (%d, %d)[w=%d]\n", ql, qr, qv.u, qv.v, qv.w);
	if(ql <= l && r <= qr) { t[x].emplace_back(qv); return; }
	int mid = (l + r) >> 1;
	if(ql <= mid) insert(ql, qr, qv, x << 1, l, mid);
	if(qr > mid) insert(ql, qr, qv, x << 1 | 1, mid + 1, r);
}

LL out[M];
std::vector<int> undo;
LL sum;
void link_(int u, int v, int w, int id) {
	// printf("link %d %d w=%d\n", u, v, w);
	assert(id > n);
	lct.makeroot(u);
	sum += w;
	if(lct.findroot(v) == u) {
		lct.split(u, v);
		int e = lct.s[v];
		// printf("e = %d (v=%d)\n", e, lct.v[e]);
		assert(e > n);
		if(lct.v[e] <= w) sum -= w, undo.emplace_back(-1);
		else {
			int p = cu[e], q = cv[e];
			sum -= lct.v[e];
			lct.cut(p, e), lct.cut(q, e);
			// lct.v[id] = w;
			lct.link(u, id), lct.link(v, id);
			undo.emplace_back(e);
		}
	} else {
		lct.link(u, id), lct.link(v, id);
		undo.emplace_back(0);
	}
	// printf("sum = %lld\n", sum);
}
void undo_(int u, int v, int w, int id) {
	// printf("undo %d %d w=%d\n", u, v, w);
	sum -= w;
	lct.cut(u, id), lct.cut(v, id);
	if(undo.back() == -1) sum += w;
	else if(undo.back()) {
		int e = undo.back();
		int p = cu[e], q = cv[e];
		sum += lct.v[e];
		lct.link(p, e), lct.link(q, e);
	}
	undo.pop_back();
	// printf("sum = %lld\n", sum);
}
void solve(int x = 1, int l = 0, int r = K) {
	for(auto [u, v, w, id] : t[x]) link_(u, v, w, id);
	if(l == r) out[l] = sum; // , puts("get answer");
	else {
		int mid = (l + r) >> 1;
		solve(x << 1, l, mid), solve(x << 1 | 1, mid + 1, r);
	}
	for(auto [u, v, w, id] : t[x]) undo_(u, v, w, id);
}

int main() {
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= m; i++) scanf("%d%d%d", &eu[i], &ev[i], &ew[i]), last[i] = 0;
	int cn = n;
	for(int q = 1; q <= K; q++) {
		int i, v;
		scanf("%d%d", &i, &v);
		insert(last[i], q - 1, {eu[i], ev[i], ew[i], ++cn}), cu[cn] = eu[i], cv[cn] = ev[i], lct.modify(cn, ew[i]), ew[i] = v, last[i] = q;
	}
	for(int i = 1; i <= m; i++) insert(last[i], K, {eu[i], ev[i], ew[i], ++cn}), cu[cn] = eu[i], cv[cn] = ev[i], lct.modify(cn, ew[i]);
	lct.v[0] = -INF - 1;
	for(int i = 1; i <= n; i++) lct.modify(i, -INF);
	solve();
	for(int i = 1; i <= K; i++) printf("%lld\n", out[i]);
	return 0;
}