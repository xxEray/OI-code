#include <bits/stdc++.h>

typedef long long LL;

const int N = 2000 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int SQRTV = 1000;

int n, m;
int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

inline void mod(int &x) { (x >= MOD) && (x -= MOD); }

bool vis[N];
int sz[N];

std::vector<int> vct;
int ans;
int dfn[N], idfn[N], cn;
int fbuf[N][N];
inline int &f(int i, int j) { return fbuf[i][j <= SQRTV ? j : m / j + SQRTV + 1]; }
void dfs(int u, int fa) {
	dfn[u] = ++cn, idfn[dfn[u]] = u;
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to] && edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		sz[u] += sz[v];
	}
}
void calc(int rt) {
	cn = 0;
	dfs(rt, 0);
	for(int i = 0; i <= cn + 1; i++) for(int j : vct) f(i, j) = 0;
	f(1, m) = 1;
	for(int i = 1; i <= cn; i++) {
		int u = idfn[i];
		for(int j : vct) {
			mod(f(i + 1, j / a[u]) += f(i, j));
			mod(f(i + sz[u], j) += f(i, j));
		}
	}
	mod(ans += MOD - 1);
	for(int j : vct) mod(ans += f(cn + 1, j));
	// printf("calc %d: ans = %d\n", rt, ans);
}

int root, rootwt, allsize;
void getroot(int u, int fa) {
	int mx = 0;
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && !vis[edge[i].to]) {
		int v = edge[i].to;
		getroot(v, u);
		sz[u] += sz[v];
		mx = std::max(mx, sz[v]);
	}
	mx = std::max(mx, allsize - sz[u]);
	if(rootwt > mx) root = u, rootwt = mx;
}
void solve(int u) {
	// printf("solve %d\n", u);
	calc(u);
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		getroot(v, 0);
		root = 0, rootwt = INF, allsize = sz[v], getroot(v, 0), solve(root);
	}
}

int main() {
#ifndef DEBUG
	freopen("fn.in", "r", stdin);
	freopen("fn.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int j = 1; j <= m; j = m / (m / j) + 1) vct.push_back(m / j);
	root = 0, rootwt = INF, allsize = n, getroot(1, 0), solve(root);
	printf("%d\n", ans);
	return 0;
}