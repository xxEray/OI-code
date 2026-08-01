#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 5e5 + 5;
const int M = 1e6 + 5;
const LL MOD = 1e9 + 7;
const LL inv2 = (MOD + 1) / 2;

int n, m;
bool cut[M << 1];
struct Graph {
	struct Edge { int to, nxt; } edge[M << 1];
	int head[N], ek;
	void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }
	Graph() : ek(2) {}
} G, Tr;

int dfn[N], low[N], bl[N];
int time_stamp;
void tarjan(int u, int fa) {
	dfn[u] = low[u] = ++time_stamp;
	for(int i = G.head[u]; i; i = G.edge[i].nxt) {
		int v = G.edge[i].to;
		if(!dfn[v]) {
			tarjan(v, i);
			if(low[v] == dfn[v]) cut[i] = true, cut[i ^ 1] = true;
			low[u] = std::min(low[u], low[v]);
		} else if(i != (fa ^ 1)) low[u] = std::min(low[u], dfn[v]);
	}
}

int scc;
int sz[N];
bool vis[N];
void dfs(int u) {
	vis[u] = true, bl[u] = scc, sz[scc]++;
	for(int i = G.head[u]; i; i = G.edge[i].nxt) if(!cut[i] && !vis[G.edge[i].to]) dfs(G.edge[i].to);
}

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

LL f[N][3];
void dp(int u, int fa) {
	f[u][0] = qpow(2, sz[u]), f[u][2] = 1;
	int son = 0;
	for(int i = Tr.head[u]; i; i = Tr.edge[i].nxt) if(Tr.edge[i].to != fa) {
		int v = Tr.edge[i].to;
		dp(v, u);
		son++;
	}
	for(int i = Tr.head[u]; i; i = Tr.edge[i].nxt) if(Tr.edge[i].to != fa) {
		int v = Tr.edge[i].to;
		f[u][0] = (f[v][0] * f[u][0] % MOD * inv2 % MOD + f[u][0] * inv2 % MOD) % MOD;
		f[u][2] = (f[v][2] * f[u][2] % MOD * inv2 % MOD + f[u][2] * inv2 % MOD) % MOD;
		(f[u][1] += f[v][1] % MOD + (f[v][0] + MOD - f[v][2]) % MOD % MOD * inv2 % MOD) %= MOD;
	}
}

int main() {
#ifndef DEBUG
	freopen("barrack.in", "r", stdin);
	freopen("barrack.out", "w", stdout);
#endif
	// freopen("D:/Useless/Temp/barrack/barrack4.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); G.add_edge(u, v); G.add_edge(v, u); }
	tarjan(1, 0);
	for(int i = 1; i <= n; i++) if(!vis[i]) scc++, dfs(i);
	for(int u = 1; u <= n; u++) for(int i = G.head[u]; i; i = G.edge[i].nxt) if(cut[i]) {
		int v = G.edge[i].to;
		if(bl[u] < bl[v]) Tr.add_edge(bl[u], bl[v]), Tr.add_edge(bl[v], bl[u]);
	}
	dp(bl[1], 0);
	// printf("scc = %d\n", scc);
	// for(int i = 1; i <= scc; i++) printf("%d %lld %lld %lld\n", sz[i], f[i][0], f[i][1], f[i][2]);
	printf("%lld\n", (f[bl[1]][0] + MOD - f[bl[1]][2] + f[bl[1]][1]) % MOD * qpow(2, m) % MOD);
	return 0;
}