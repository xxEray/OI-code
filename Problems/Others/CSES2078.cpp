#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 1e9 + 7;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int n, m;

bool vis[N];
int cnt = 0;
void dfs(int u, int fa) {
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(!vis[v]) cnt++, dfs(v, u);
	}
}

LL qpow(LL a, LL b) { LL ret = 1; while(true) { if(b & 1) ret = ret * a % MOD; if(!(b >>= 1)) return ret; a = a * a % MOD; } }

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i, 0);
	printf("%lld\n", qpow(2, m - cnt));
	return 0;
}