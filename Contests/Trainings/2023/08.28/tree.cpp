#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;
const LL MOD = 998244353;

int n, Ttype;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

LL f[3][N], g[3][N];
LL pre[2][2][N], suf[2][2][N];
int son[N];
void dfs(int u, int fa) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) dfs(edge[i].to, u);
	int sz = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) son[++sz] = edge[i].to;
	son[sz + 1] = 0;
	for(int i = 0; i <= sz + 1; i++) pre[0][0][i] = pre[1][0][i] = pre[0][1][i] = pre[1][1][i] = 0;
	for(int i = 0; i <= sz + 1; i++) suf[0][0][i] = suf[1][0][i] = suf[0][1][i] = suf[1][1][i] = 0;
	pre[0][0][0] = 1;
	for(int i = 1; i <= sz; i++)
		for(int j = 0; j <= 1; j++)
			for(int k = 0; k <= 1; k++) {
				(pre[j][k][i] += pre[j][k][i - 1] * f[0][son[i]]) %= MOD;
				if(j) (pre[j][k][i] += pre[j - 1][k][i - 1] * f[1][son[i]]) %= MOD;
				if(k) (pre[j][k][i] += pre[j][k - 1][i - 1] * f[2][son[i]]) %= MOD;
			}
	suf[0][0][sz + 1] = 1;
	for(int i = sz; i >= 1; i--)
		for(int j = 0; j <= 1; j++)
			for(int k = 0; k <= 1; k++) {
				(suf[j][k][i] += suf[j][k][i + 1] * f[0][son[i]]) %= MOD;
				if(j) (suf[j][k][i] += suf[j - 1][k][i + 1] * f[1][son[i]]) %= MOD;
				if(k) (suf[j][k][i] += suf[j][k - 1][i + 1] * f[2][son[i]]) %= MOD;
			}
	f[0][u] = (pre[1][1][sz] + pre[0][0][sz]) % MOD, f[1][u] = pre[0][0][sz], f[2][u] = pre[1][0][sz];
	(g[0][u] += pre[1][1][sz]) %= MOD;
	for(int i = 1; i <= sz; i++) {
		(g[0][u] += g[0][son[i]] * pre[0][0][i - 1] % MOD * suf[0][0][i + 1]) %= MOD;
		(g[0][u] += g[0][son[i]] * (pre[0][0][i - 1] * suf[1][1][i + 1] % MOD + pre[0][1][i - 1] * suf[1][0][i + 1] % MOD)) %= MOD;
		(g[0][u] += g[0][son[i]] * (pre[1][0][i - 1] * suf[0][1][i + 1] % MOD + pre[1][1][i - 1] * suf[0][0][i + 1] % MOD)) %= MOD;
		(g[0][u] += g[1][son[i]] * (pre[0][0][i - 1] * suf[0][1][i + 1] % MOD + pre[0][1][i - 1] * suf[0][0][i + 1] % MOD)) %= MOD;
		(g[0][u] += g[2][son[i]] * (pre[0][0][i - 1] * suf[1][0][i + 1] % MOD + pre[1][0][i - 1] * suf[0][0][i + 1] % MOD)) %= MOD;
		(g[1][u] += g[0][son[i]] * pre[0][0][i - 1] % MOD * suf[0][0][i + 1]) %= MOD;
		(g[2][u] += g[0][son[i]] * (pre[0][0][i - 1] * suf[1][0][i + 1] % MOD + pre[1][0][i - 1] * suf[0][0][i + 1] % MOD)) %= MOD;
		(g[2][u] += g[1][son[i]] * pre[0][0][i - 1] % MOD * suf[0][0][i + 1]) %= MOD;
	}
}

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	scanf("%d%d", &n, &Ttype);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0);
	printf("%lld\n", f[0][1]);
	if(Ttype) printf("%lld\n", g[0][1]);
	return 0;
}