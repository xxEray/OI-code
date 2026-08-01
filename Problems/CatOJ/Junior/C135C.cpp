#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

typedef long long LL;

const int N = 3e5 + 5;
const LL MOD = 1e9 + 7;

int n, Q;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int go[21][N], dep[N];
void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1, go[0][u] = fa;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
	}
}
void preprocess() {
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n; i++)
			go[j][i] = go[j - 1][go[j - 1][i]];
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	for(int i = 0; i <= 20; i++) if((dep[u] - dep[v]) >> i & 1) u = go[i][u];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--) if(go[i][u] != go[i][v]) u = go[i][u], v = go[i][v];
	return go[0][u];
}

struct dsu {
	int fa[N * 2];
	int t;
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) {
		// printf("merge%d %d %d\n", t, x, y);
		x = find(x), y = find(y);
		if(y > n || dep[x] < dep[y]) fa[y] = x;
		else fa[x] = y;
	}
} dir, acc; // direction, accessibility

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

std::vector<std::pair<int, int>> vct;

int main() {
	acc.t = 1;
	scanf("%d%d", &n, &Q);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0);
	preprocess();
	for(int i = 1; i <= 2 * n; i++) dir.fa[i] = acc.fa[i] = i;
	while(Q--) {
		int u, v;
		scanf("%d%d", &u, &v);
		int f = lca(u, v);
		int ou = u, ov = v;
		if(u != f && v != f) dir.merge(ou, ov + n), dir.merge(ov, ou + n), vct.push_back({ou, ov});
		int fu = u, fv = v;
		for(int i = 0; i <= 20; i++) if((dep[u] - dep[f] - 1) >> i & 1) fu = go[i][fu];
		for(int i = 0; i <= 20; i++) if((dep[v] - dep[f] - 1) >> i & 1) fv = go[i][fv];
		assert((fu != 0 && fu != 1) || u == f);
		assert((fv != 0 && fv != 1) || v == f);
		u = acc.find(u), v = acc.find(v);
		// printf("u=%d, v=%d, f=%d, fu=%d, fv=%d\n", u, v, f, fu, fv);
		if(ou != f) {
			while(u != acc.find(fu)) dir.merge(u, ou), dir.merge(u + n, ou + n), acc.merge(u, ou), u = acc.find(go[0][u]), assert(u <= n);
			dir.merge(u, ou), dir.merge(u + n, ou + n), acc.merge(u, ou);
		}
		if(ov != f) {
			while(v != acc.find(fv)) dir.merge(v, ov), dir.merge(v + n, ov + n), acc.merge(v, ov), v = acc.find(go[0][v]), assert(v <= n);
			dir.merge(v, ov), dir.merge(v + n, ov + n), acc.merge(v, ov);
		}
	}
	bool flag = true;
	for(int i = 1; i <= n; i++) flag &= dir.find(i) != dir.find(i + n);
	if(!flag) { puts("0"); return 0; }
	for(auto &p : vct) acc.merge(p.first, p.second);
	// puts("---");
	int cnt = 0;
	for(int i = 2; i <= n; i++) cnt += acc.find(i) == i;
	printf("%lld\n", qpow(2, cnt));
	return 0;
}