#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;
const LL MOD = 998244353;

int n, Ttype;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

struct DP {
	LL cnt, sum;
	DP() {}
	DP(LL cnt_, LL sum_) : cnt(cnt_), sum(sum_) {}
	friend DP operator+(const DP &x, const DP &y) { return DP((x.cnt + y.cnt) % MOD, (x.sum + y.sum) % MOD); }
	friend DP operator*(const DP &x, const DP &y) { return DP(x.cnt * y.cnt % MOD, (x.cnt * y.sum + y.cnt * x.sum) % MOD); }
	DP &operator+=(const DP &x) { return *this = *this + x; }
};

DP f[3][N];
void dfs(int u, int fa) {
	DP g[2][2], h[2][2];
	g[0][0] = DP(1, 0), g[0][1] = g[1][0] = g[1][1] = DP(0, 0);
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		for(int j = 0; j <= 1; j++) for(int k = 0; k <= 1; k++) h[j][k] = g[j][k], g[j][k] = DP(0, 0);
		for(int j = 0; j <= 1; j++) for(int k = 0; k <= 1; k++) g[j][k] += h[j][k] * f[0][v];
		for(int k = 0; k <= 1; k++) g[1][k] += h[0][k] * f[1][v];
		for(int j = 0; j <= 1; j++) g[j][1] += h[j][0] * f[2][v];
	}
	f[0][u] = g[1][1] * DP(1, 1) + g[0][0], f[1][u] = g[0][0], f[2][u] = g[1][0];
}

int main() {
	scanf("%d%d", &n, &Ttype);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0);
	printf("%lld\n", f[0][1].cnt);
	if(Ttype) printf("%lld\n", f[0][1].sum);
	return 0;
}