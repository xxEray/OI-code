#include <bits/stdc++.h>

typedef long long LL;

const int N = 60 + 5;
const int M = 15 + 4;
const LL MOD = 1e9 + 7;

int n, m, K;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

int ld[N];
int find(int x) { return x == ld[x] ? x : ld[x] = find(ld[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? ld[x] = y : 0; }

int fa[N];
void dfs(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		dfs(v);
	}
}

bool vis[N];
std::vector<int> path[M];

int main() {
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1);
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		for(int j = 1; j <= n; j++) vis[j] = false;
		for(int j = u; j; j = fa[j]) vis[j] = true;
		int lca;
		for(lca = v; lca && !vis[lca]; lca = fa[lca]);
		for(int j = u; j != lca; j = fa[j]) path[i].push_back(j);
		std::vector<int> tmp;
		for(int j = v; j != lca; j = fa[j]) tmp.push_back(j);
		std::reverse(tmp.begin(), tmp.end());
		path[i].insert(path[i].end(), tmp.begin(), tmp.end());
		// printf("%d->%d: ", u, v); for(int x : path[i]) printf("%d ", x); puts("");
	}
	LL ans = 0;
	int U = (1 << m) - 1;
	for(int s = 0; s <= U; s++) {
		for(int i = 1; i <= n; i++) ld[i] = i;
		for(int i = 1; i <= m; i++) if(s >> (i - 1) & 1) {
			int rep = path[i].front();
			for(int x : path[i]) merge(x, rep);
		}
		int cnt = 0;
		for(int i = 2; i <= n; i++) cnt += (find(i) == i);
		// printf("s = %d, cnt = %d\n", s, cnt);
		(ans += ((__builtin_popcount(s) & 1) ? MOD - 1 : 1) * qpow(K, cnt)) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
} /*
11 7 2
7 6
11 7
9 7
5 9
2 6
1 5
8 1
10 9
3 8	
4 11
6 9
2 4
7 5
1 3
11 6
6 5
1 11
*/