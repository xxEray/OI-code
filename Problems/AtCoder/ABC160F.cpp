#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 1e9 + 7;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int n;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

int fa[N];
LL size[N], f[N], g[N], tmp[N], ans[N];

void dfs_f(int u) {
	f[u] = 1, size[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		dfs_f(v);
		(f[u] *= f[v] * invfac[size[v]] % MOD) %= MOD;
		size[u] += size[v];
	}
	(f[u] *= fac[size[u] - 1]) %= MOD;
}
void dfs_g(int u) {
	tmp[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(v == fa[u]) continue;
		(tmp[u] *= f[v] * invfac[size[v]] % MOD) %= MOD;
	}
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) dfs_g(edge[i].to);
}
void get_g(int u) {
	if(u == 1) g[u] = 1;
	else g[u] = g[fa[u]] * fac[n - size[u] - 1] % MOD * invfac[n - size[fa[u]]] % MOD;
	if(u != 1) (g[u] *= tmp[fa[u]] * inv(f[u]) % MOD * fac[size[u]] % MOD) %= MOD;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) get_g(edge[i].to);
}
void dfs_ans(int u) {
	ans[u] = g[u] * fac[n - 1] % MOD * invfac[n - size[u]] % MOD;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		(ans[u] *= f[v] * invfac[size[v]] % MOD) %= MOD;
		dfs_ans(v);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[n] = inv(fac[n]);
	for(int i = n; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
	g[0] = 1;
	dfs_f(1), dfs_g(1), get_g(1), dfs_ans(1);
	// for(int i = 1; i <= n; i++) printf("%d: f = %lld, g = %lld, ans = %lld\n", i, f[i], g[i], ans[i]);
	for(int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
	return 0;
}