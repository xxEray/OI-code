#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int n, K;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int sz[N];
void dfs(int u, int fa) {
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		sz[u] += sz[v];
	}
}

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	if(K & 1) { puts("1"); return 0; }
	get_factorial(n);
	dfs(1, 0);
	LL ans = C(n, K);
	for(int u = 1; u <= n; u++) for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(sz[u] > sz[v]) continue;
		if(sz[u] >= K / 2 && n - sz[u] >= K / 2) (ans += C(sz[u], K / 2) * C(n - sz[u], K / 2) % MOD) %= MOD;
	}
	// printf("ans = %lld\n", ans);
	printf("%lld\n", ans * inv(C(n, K)) % MOD);
	return 0;
}