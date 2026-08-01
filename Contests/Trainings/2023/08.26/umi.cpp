#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 998244353;

int n, m, Q, Tid;
int a[N];
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

LL catalan[N];
int fa[21][N], dep[N], jmp[21][N], cnt[N];
LL pre[N];
void dfs(int u) {
	dep[u] = dep[fa[0][u]] + 1;
	cnt[u] = (a[u] == a[fa[0][u]] ? cnt[fa[0][u]] + 1 : 1);
	jmp[0][u] = (a[u] == a[fa[0][u]] ? jmp[0][fa[0][u]] : u);
	pre[u] = pre[fa[0][jmp[0][u]]] * catalan[cnt[u]] % MOD;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[0][u]) {
		int v = edge[i].to;
		fa[0][v] = u;
		dfs(v);
	}
}
void binary_lifting() {
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n; i++) {
			fa[j][i] = fa[j - 1][fa[j - 1][i]];
			jmp[j][i] = jmp[j - 1][fa[0][jmp[j - 1][i]]];
		}
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	for(int i = 0; i <= 20; i++) if((dep[u] - dep[v]) >> i & 1) u = fa[i][u];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--) if(fa[i][u] != fa[i][v]) u = fa[i][u], v = fa[i][v];
	return fa[0][u];
}

int main() {
#ifndef DEBUG
	freopen("umi.in", "r", stdin);
	freopen("umi.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &Tid);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	get_factorial(m);
	for(int i = 0; i <= n; i++) catalan[i] = C(2 * i, i) * inv(i + 1) % MOD;
	pre[0] = 1;
	dfs(1);
	binary_lifting();
	// printf("contribution: "); for(int i = 0; i <= n; i++) printf("%lld ", catalan[i]); puts("");
	// for(int i = 0; i <= n; i++) printf("%d: fa = %d, cnt = %d, dep = %d, jmp = %d, pre = %lld\n", i, fa[0][i], cnt[i], dep[i], jmp[0][i], pre[i]);
	scanf("%d", &Q);
	while(Q--) {
		int u, v;
		scanf("%d%d", &u, &v);
		int f = lca(u, v);
		// printf("f = %d\n", f);
		int len = dep[u] + dep[v] - 2 * dep[f] + 1;
		// printf("len = %d\n", len);
		int tu = u, tv = v;
		for(int i = 20; i >= 0; i--) if(dep[jmp[i][tu]] > dep[f]) tu = fa[0][jmp[i][tu]];
		for(int i = 20; i >= 0; i--) if(dep[jmp[i][tv]] > dep[f]) tv = fa[0][jmp[i][tv]];
		// printf("tu = %d, tv = %d\n", tu, tv);
		LL ret = 1;
		(ret *= pre[u] * inv(pre[tu]) % MOD) %= MOD;
		(ret *= pre[v] * inv(pre[tv]) % MOD) %= MOD;
		(ret *= catalan[dep[tu] + dep[tv] - 2 * dep[f] + 1]) %= MOD;
		(ret *= C(m, 2 * len)) %= MOD;
		printf("%lld\n", ret);
	}
	return 0;
} /*

*/