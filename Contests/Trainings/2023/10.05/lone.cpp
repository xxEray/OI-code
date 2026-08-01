#include <bits/stdc++.h>

typedef long long LL;

const int N = 5000 + 5;
const int MAXS = (1 << 6) + 5;
const LL MOD = 998244353;

int n, K;
int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

int U;
int fa[N];
std::vector<int> son[N];
int sz[N];
int sum[MAXS];
void dfs0(int u) {
	sz[u] = 1;
	son[u].push_back(0);
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		dfs0(v);
		son[u].push_back(v);
		sz[u] += sz[v];
	}
	son[u].push_back(0);
}

LL f[N][MAXS], g[N][MAXS], tmp[MAXS];
std::vector<LL> fl[N][MAXS], fr[N][MAXS];
void dfs1(int u) {
	int len = son[u].size() - 2;
	for(int s = 0; s <= U; s++) fl[u][s].resize(len + 2), fr[u][s].resize(len + 2);
	for(int i = 1; i <= len; i++) dfs1(son[u][i]);
	fl[u][0][0] = 1;
	for(int i = 1; i <= len; i++) {
		int v = son[u][i];
		for(int s = 0; s <= U; s++)
			for(int t = s; ; t = (t - 1) & s) {
				(fl[u][s][i] += fl[u][t][i - 1] * f[v][s ^ t]) %= MOD;
				if(!t) break;
			}
	}
	fr[u][0][len + 1] = 1;
	for(int i = len; i >= 1; i--) {
		int v = son[u][i];
		for(int s = 0; s <= U; s++)
			for(int t = s; ; t = (t - 1) & s) {
				(fr[u][s][i] += fr[u][t][i + 1] * f[v][s ^ t]) %= MOD;
				if(!t) break;
			}
	}
	for(int s = 0; s <= U; s++) {
		f[u][s] = fl[u][s][len];
		if(sum[s] == sz[u])
			for(int i = K; i >= 1; i--) if(s >> (i - 1) & 1) {
				(f[u][s] += fl[u][s ^ (1 << (i - 1))][len]) %= MOD;
				break;
			}
	}
}

void dfs2(int u) {
	int len = son[u].size() - 2;
	for(int i = 1; i <= len; i++) {
		int v = son[u][i];
		for(int s = 0; s <= U; s++) tmp[s] = 0;
		for(int s = 0; s <= U; s++)
			for(int t = s; ; t = (t - 1) & s) {
				(tmp[s] += fl[u][t][i - 1] * fr[u][s ^ t][i + 1]) %= MOD;
				if(!t) break;
			}
		for(int s = U; s >= 0; s--) {
			(tmp[s] *= g[u][0]) %= MOD;
			for(int t = s; t; t = (t - 1) & s)
				(tmp[s] += g[u][t] * tmp[s ^ t]) %= MOD;
		}
		for(int s = 0; s <= U; s++) {
			g[v][s] = tmp[s];
			if(sum[s] == n - sz[v])
				for(int j = K; j >= 1; j--) if(s >> (j - 1) & 1) {
					(g[v][s] += tmp[s ^ (1 << (j - 1))]) %= MOD;
					break;
				}
		}
		dfs2(v);
	}
}

int main() {
#ifndef DEBUG
	freopen("lone.in", "r", stdin);
	freopen("lone.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	scanf("%d", &K);
	for(int i = 1; i <= K; i++) scanf("%d", &a[i]);
	a[0] = a[K];
	for(int i = K; i >= 1; i--) a[i] = (i == 1 ? n : a[i - 1]) - a[i];
	// for(int i = 1; i <= K; i++) printf("%d ", a[i]);
	// printf("(%d)\n", a[0]);
	U = (1 << K) - 1;
	for(int s = 0; s <= U; s++) for(int i = 1; i <= K; i++)
		if(s >> (i - 1) & 1) sum[s] += a[i];
	g[1][0] = 1;
	dfs0(1), dfs1(1), dfs2(1);
	LL ans = 0;
	for(int u = 1; u <= n; u++)
		for(int s = 0; s <= U; s++)
			if(sum[s] != sz[u]) (ans += f[u][s] * g[u][U ^ s]) %= MOD;
	// for(int i = 1; i <= n; i++)
	// 	for(int s = 0; s <= U; s++)
	// 		printf("[%d][%d]: f = %lld, g = %lld\n", i, s, f[i][s], g[i][s]);
	// printf("sum = %lld\n", ans);
	printf("%lld\n", ans * inv(a[0]) % MOD);
	return 0;
} /*
3
1 2
2 3
2
2 1
*/