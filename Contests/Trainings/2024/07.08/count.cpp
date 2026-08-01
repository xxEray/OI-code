#include <bits/stdc++.h>

typedef long long LL;

const int N = 200 + 5;
const LL MOD = 998244353;

int n, m;
struct Edge { int to, nxt, w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

LL fac[N], invfac[N], fac2[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(LL x, LL y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
	fac2[0] = 1;
	for(int i = 2; i <= mx; i += 2) fac2[i] = fac2[i - 2] * (i - 1) % MOD;
}

int U, es;
int sz[N];
LL f[N][N], tmp[N];
LL x;
bool vis[N];
void dfs(int u, int fa) {
	vis[u] = true;
	sz[u] = 1;
	f[u][0] = 0, f[u][1] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && (~es >> (edge[i].w - 1) & 1)) {
		int v = edge[i].to;
		dfs(v, u);
		for(int j = 1; j <= sz[u] + sz[v]; j++) tmp[j] = 0;
		for(int j = 1; j <= sz[u]; j++) for(int k = 1; k <= sz[v]; k++) {
			(tmp[j + k] += f[u][j] * f[v][k] % MOD) %= MOD;
			(tmp[j] += f[u][j] * f[v][k] % MOD * fac2[k] % MOD * x) %= MOD;
		}
		for(int j = 1; j <= sz[u] + sz[v]; j++) f[u][j] = tmp[j];
		sz[u] += sz[v];
	}
	// for(int i = 0; i <= sz[u]; i++) printf("f[%d][%d] = {%lld, %lld}\n", u, i, f[u][i][0], f[u][i][1]);
}

LL val[N], ret[N];
LL tp[N];
void lagrange() {
	int mx = (n + 1) / 2 + 1;
	for(int i = 0; i < mx; i++) ret[i] = 0;
	// for(int i = 1; i <= mx; i++) printf("val[%d] = %lld\n", i, val[i]);
	for(int i = 1; i <= mx; i++) {
		for(int j = 0; j < mx; j++) tp[j] = 0;
		tp[0] = 1;
		for(int j = 1; j <= mx; j++) if(j != i) {
			LL vv = inv(i - j);
			for(int k = mx - 1; k >= 1; k--) tp[k] = (tp[k - 1] * vv - tp[k] * j % MOD * vv % MOD + MOD) % MOD;
			tp[0] = (MOD - tp[0] * j % MOD * vv % MOD) % MOD;
		}
		// printf("tp(i=%d): ", i); for(int j = 0; j < mx; j++) printf("%lld ", tp[j]); puts("");
		for(int j = 0; j < mx; j++) (ret[j] += tp[j] * val[i]) %= MOD;
	}
}

LL ans[N];
void include_and_exclude() {
	for(es = 0; es <= U; es++) {
		// printf("es = %d\n", es);
		for(int i = 0; i <= (n + 1) / 2; i++) ret[i] = 0;
		int cnt = 0;
		for(x = 1; x <= (n + 1) / 2 + 1; x++) {
			for(int i = 1; i <= n; i++) vis[i] = false;
			val[x] = 1;
			for(int i = 1; i <= n; i++) if(!vis[i]) {
				if(x == 1) cnt++;
				dfs(i, 0);
				LL sum = 0;
				for(int j = 2; j <= sz[i]; j += 2) (sum += f[i][j] * fac2[j]) %= MOD;
				(val[x] *= sum) %= MOD;
			}
		}
		lagrange();
		// for(int i = 0; i <= (n + 1) / 2; i++) printf("ret[%d] = %lld\n", i, ret[i]);
		for(int i = 0; i <= (n + 1) / 2; i++) for(int j = i + 1; j <= (n + 1) / 2; j++)
			(ret[i] += ((i - j) & 1 ? MOD - 1 : 1) * C(j, i) % MOD * ret[j]) %= MOD;
		cnt--;
		for(int i = (n + 1) / 2; i >= cnt; i--) ret[i] = ret[i - cnt];
		for(int i = cnt - 1; i >= 0; i--) ret[i] = 0;
		// for(int i = 0; i <= (n + 1) / 2; i++) printf("ret[%d] = %lld\n", i, ret[i]);
		LL op = (__builtin_popcount(es) & 1 ? MOD - 1 : 1);
		for(int i = 0; i <= (n + 1) / 2; i++) (ans[i] += op * ret[i]) %= MOD;
	}
}

int main() {
#ifndef DEBUG
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
	get_factorial(200);
	U = (1 << m) - 1;
	include_and_exclude();
	for(int i = 0; i <= n - 1; i++) printf("%lld\n", ans[i]);
	return 0;
} /*
6 2
1 2 2
1 3 1
2 4 2
4 5 1
2 6 1
*/