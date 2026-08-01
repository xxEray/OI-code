#include <cstdio>
#include <algorithm>
#include <vector>
#include <array>

const int N = 2e5 + 5;

int n, Q;
int a[N];
std::vector<int> to[N], son[N];

int fa[N], dep[N], id[N];
int dfn[N], sz[N];
int time_stamp;
void dfs1(int u) {
	dfn[u] = ++time_stamp;
	sz[u] = 1;
	for(int v : to[u]) if(v != fa[u]) {
		fa[v] = u, dep[v] = dep[u] + 1;
		dfs1(v);
		sz[u] += sz[v];
		son[u].push_back(v), id[v] = (int)son[u].size() - 1;
	}
}
bool ancestor(int u, int v) { return dfn[u] <= dfn[v] && dfn[v] <= dfn[u] + sz[u] - 1; }

std::array<int, 31> f[N], g[N], ans;
std::vector<std::array<int, 31>> tl[N], tr[N];
void insert(std::array<int, 31> &x, int y) {
	for(int i = 30; i >= 0; i--) if(y >> i & 1) {
		if(x[i]) y ^= x[i];
		else { x[i] = y; break; }
	}
}
void dfs2(int u) {
	insert(f[u], a[u]);
	for(int v : son[u]) {
		dfs2(v);
		for(int i = 0; i <= 30; i++) if(f[v][i]) insert(f[u], f[v][i]);
	}
}
void dfs3(int u) {
	insert(g[u], a[u]);
	for(int j = 0; j <= 30; j++) insert(g[u], g[fa[u]][j]);
	for(int v : son[u]) dfs3(v);
}

int go[21][N];
void preprocess() {
	for(int i = 1; i <= n; i++) go[0][i] = fa[i];
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n; i++)
			go[j][i] = go[j - 1][go[j - 1][i]];
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		time_stamp = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) to[i].clear(), son[i].clear(), f[i].fill(0), g[i].fill(0), tl[i].clear(), tr[i].clear();
		for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); to[u].push_back(v), to[v].push_back(u); }
		dfs1(1);
		dfs2(1);
		for(int u = 1; u <= n; u++) {
			int c = son[u].size();
			for(int i = 0; i < c; i++) tl[u].push_back(std::array<int, 31>()), tr[u].push_back(std::array<int, 31>());
			for(int i = 0; i < c; i++) {
				int v = son[u][i];
				if(i > 0) tl[u][i] = tl[u][i - 1];
				for(int j = 0; j <= 30; j++) if(f[v][j]) insert(tl[u][i], f[v][j]);
			}
			for(int i = c - 1; i >= 0; i--) {
				int v = son[u][i];
				if(i < c - 1) tr[u][i] = tr[u][i + 1];
				for(int j = 0; j <= 30; j++) if(f[v][j]) insert(tr[u][i], f[v][j]);
			}
			for(int i = 0; i < c; i++) {
				int v = son[u][i];
				if(i > 0) for(int j = 0; j <= 30; j++) if(tl[u][i - 1][j]) insert(g[v], tl[u][i - 1][j]);
				if(i < c - 1) for(int j = 0; j <= 30; j++) if(tr[u][i + 1][j]) insert(g[v], tr[u][i + 1][j]);
			}
		}
		dfs3(1);
		preprocess();
		scanf("%d", &Q);
		while(Q--) {
			int r, x;
			scanf("%d%d", &r, &x);
			if(r == x) ans = f[1];
			else if(ancestor(x, r)) {
				ans = g[x];
				int d = dep[r] - dep[x] - 1;
				for(int i = 0; i <= 20; i++) if(d >> i & 1) r = go[i][r];
				int e = id[r];
				if(e > 0) for(int i = 0; i <= 30; i++) if(tl[x][e - 1][i]) insert(ans, tl[x][e - 1][i]);
				if(e < (int)son[x].size() - 1) for(int i = 0; i <= 30; i++) if(tr[x][e + 1][i]) insert(ans, tr[x][e + 1][i]);
			} else ans = f[x];
			int ret = 0;
			for(int j = 30; j >= 0; j--) if(!(ret >> j & 1)) ret ^= ans[j];
			printf("%d\n", ret);
		}
	}
	return 0;
} /*
1
6
12 12 8 25 6 1
1 5
1 2
2 6
2 3
2 4
3
4 2
3 5
1 2
*/