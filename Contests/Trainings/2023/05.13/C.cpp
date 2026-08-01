#include <bits/stdc++.h>

typedef long long LL;

const int N = 700 + 5;
const LL MOD = 1e9 + 7;

int n;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

LL fac[N], invfac[N], power2[N * N];
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

LL f[N][N], ans[N], tmp[N];
LL vx;
void dp(int u, int fa) {
	for(int i = 0; i <= sz[u]; i++) f[u][i] = 0;
	int cnt = 1;
	f[u][1] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dp(v, u);
		for(int j = 0; j <= cnt + sz[v]; j++) tmp[j] = 0;
		for(int j = 0; j <= cnt; j++) for(int k = 0; k <= sz[v]; k++) (tmp[j + k] += f[u][j] * f[v][k]) %= MOD;
		for(int j = 0; j <= cnt + sz[v]; j++) f[u][j] = tmp[j];
		cnt += sz[v];
	}
	for(int i = 1; i <= sz[u]; i++) (f[u][0] += f[u][i] * vx % MOD * power2[i * (i - 1) / 2 - (i - 1)]) %= MOD;
}

LL g[N], h[N];
void lagrange() {
	h[0] = 1;
	for(int i = 1; i <= n + 1; i++)
		for(int j = n; j >= 0; j--)
			h[j] = ((j ? h[j - 1] : 0) + (MOD - i) * h[j]) % MOD;
	for(int i = 1; i <= n + 1; i++) {
		LL val = ans[i];
		for(int j = 1; j <= n + 1; j++) if(j != i) (val *= inv(MOD + i - j)) %= MOD;
		for(int j = 0; j <= n; j++) h[j] = ((j ? h[j - 1] : 0) + MOD - h[j]) * inv(i) % MOD;
		for(int j = 0; j <= n; j++) (g[j] += h[j] * val) %= MOD;
		for(int j = n; j >= 0; j--) h[j] = ((j ? h[j - 1] : 0) + (MOD - i) * h[j]) % MOD;
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	get_factorial(n);
	power2[0] = 1;
	for(int i = 1; i <= 490000; i++) power2[i] = power2[i - 1] * 2 % MOD;
	dfs(1, 0);
	for(int i = 1; i <= n + 1; i++) vx = i, dp(1, 0), ans[i] = f[1][0];
	lagrange();
	// for(int i = 1; i <= n + 1; i++) printf("x=%d, F=%lld\n", i, ans[i]);
	// printf("g: "); for(int i = 1; i <= n; i++) printf("%lld ", g[i]); puts("");
	for(int i = 0; i <= n; i++) h[i] = 0;
	for(int i = 0; i < n; i++)
		for(int j = i; j <= n - 1; j++)
			(h[i] += qpow(MOD - 1, j - i) * C(j, i) % MOD * g[j + 1]) %= MOD;
	for(int i = 0; i < n; i++) printf("%lld ", h[i]);
	puts("");
	return 0;
} /*
3
1 2
1 3
*/