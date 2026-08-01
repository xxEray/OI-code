#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <queue>

typedef long long LL;

const int N = 2500 + 5;
const int M = 40 + 5;
const LL MOD = 998244353;

int n, m, Q;
bool a[N << 1][30];
struct Graph {
	struct Edge { int to, nxt; } edge[N << 1];
	int head[N], k;
	Graph() : k(2) {}
	void add_edge(int u, int v) { edge[k] = (Edge){v, head[u]}, head[u] = k++; }
} Tr;

struct AC_Automaton {
	int c[M][30], fail[M];
	bool end[M];
	int tot;
	AC_Automaton() : tot(1) {}
	void insert(char *s) {
		int now = 1, len = strlen(s);
		for(int i = 0; i < len; i++) {
			if(!c[now][s[i] - 'a']) c[now][s[i] - 'a'] = ++tot;
			now = c[now][s[i] - 'a'];
		}
		end[now] = true;
	}
	void init() {
		std::queue<int> q;
		for(int i = 0; i < 26; i++) if(c[1][i]) q.push(c[1][i]);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int i = 0; i < 26; i++)
				if(c[u][i]) fail[c[u][i]] = c[fail[u]][i], q.push(c[u][i]);
				else c[u][i] = c[fail[u]][i];
		}
	}
} ac;

struct Matrix { int a[M][M]; Matrix() { memset(a, 0, sizeof(a)); }};
void mul1(Matrix &x, const Matrix &y, const Matrix &z) {
	assert(&x != &y && &x != &z);
	for(int i = 1; i <= ac.tot; i++) for(int j = 1; j <= ac.tot; j++) x.a[i][j] = 0;
	for(int i = 1; i <= ac.tot; i++)
		for(int j = 1; j <= ac.tot; j++)
			for(int k = 1; k <= ac.tot; k++) {
				x.a[i][j] += y.a[i][k] * z.a[k][j] % MOD;
				if(x.a[i][j] >= MOD) x.a[i][j] -= MOD;
			}
}
void mul2(Matrix &x, const Matrix &y, const Matrix &z) {
	assert(&x != &y && &x != &z);
	for(int i = 1; i <= ac.tot; i++) for(int j = 1; j <= ac.tot; j++) x.a[i][j] = 0;
	for(int i = 1; i <= ac.tot; i++)
		for(int j = 1; j <= ac.tot; j++) {
			x.a[1][j] += y.a[1][i] * z.a[i][j] % MOD;
			if(x.a[1][j] >= MOD) x.a[1][j] -= MOD;
		}
}

Matrix trans[N];

struct SegmentTree {
	Matrix t[N << 2];
	void build(int x = 1, int l = 1, int r = ac.tot) {

	}
	void set(int qind, const Matrix &qv, int x = 1, int l = 1, int r = ac.tot) {

	}
	const Matrix &query(int ql, int qr, int x = 1, int l = 1, int r = ac.tot) {

	}
} seg;

struct HeavyLightDecomposition { // 轻重链剖分/树链剖分
	int hson[N], dep[N], top[N], fa[N], sz[N], dfn[N];
	int time_stamp;
	void dfs1(int u) {
		sz[u] = 1;
		for(int i = Tr.head[u]; i; i = Tr.edge[i].nxt) if(Tr.edge[i].to != fa[u]) {
			int v = Tr.edge[i].to;
			fa[v] = u, dep[v] = dep[u] + 1;
			dfs1(v);
			sz[u] += sz[v];
		}
	}
	void dfs2(int u, int tp) {
		dfn[u] = ++time_stamp;
		top[u] = tp;
		for(int i = Tr.head[u]; i; i = Tr.edge[i].nxt) if(Tr.edge[i].to != fa[u] && (hson[u] == 0 || sz[Tr.edge[i].to] > sz[hson[u]])) hson[u] = Tr.edge[i].to;
		if(hson[u]) dfs2(hson[u], tp);
		for(int i = Tr.head[u]; i; i = Tr.edge[i].nxt) if(Tr.edge[i].to != fa[u] && Tr.edge[i].to != hson[u]) dfs2(Tr.edge[i].to, Tr.edge[i].to);
	}
	int lca(int u, int v) {
		while(top[u] != top[v])
			if(dep[top[u]] < dep[top[v]]) v = fa[top[v]];
			else u = fa[top[u]];
		return dep[u] < dep[v] ? u : v;
	}
	const Matrix &calc(int u, int v) {
		Matrix ret, tmp;
		while(top[u] != top[v]) {
			if(dep[top[u]] < dep[top[v]]) std::swap(u, v);
			mul2(tmp, ret, seg.query(dfn[top[u]], dfn[u]));
			u = fa[top[u]];
		}
		return ret;
	}
} hld;

int main() {
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i < n; i++) {
		int u, v;
		char str[30];
		scanf("%d%d%s", &u, &v, str);
		Tr.add_edge(u, v), Tr.add_edge(v, u);
		int len = strlen(str);
		for(int j = 0; j < len; j++) a[Tr.k - 1][str[j] - 'a'] = true, a[Tr.k - 2][str[j] - 'a'] = true;
	}
	for(int i = 1; i <= m; i++) {
		char str[50];
		scanf("%s", str);
		ac.insert(str);
	}
	ac.init();
	for(int i = 1; i < n; i++) {

	}
	return 0;
}