#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, K, Q;
LL a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int fa[N], dep[N], son[N];
void dfs(int u) {
	dep[u] = dep[fa[u]] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		dfs(v);
		if(!son[u] || a[son[u]] > a[v]) son[u] = v;
	}
}

struct Matrix { LL a[3][3]; } e, initial;
Matrix mul(Matrix x, Matrix y) {
	Matrix z;
	for(int i = 0; i < K; i++) for(int j = 0; j < K; j++) z.a[i][j] = LLINF;
	for(int i = 0; i < K; i++) for(int j = 0; j < K; j++) for(int k = 0; k < K; k++) z.a[i][k] = std::min(z.a[i][k], x.a[i][j] + y.a[j][k]);
	return z;
}
Matrix trans[N];

Matrix prod1[N][21], prod2[N][21];
int go[N][21];
void preprocess() {
	for(int i = 1; i <= n; i++) go[i][0] = fa[i], prod1[i][0] = prod2[i][0] = trans[i];
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n; i++) {
			go[i][j] = go[go[i][j - 1]][j - 1];
			prod1[i][j] = mul(prod1[i][j - 1], prod1[go[i][j - 1]][j - 1]);
			prod2[i][j] = mul(prod2[go[i][j - 1]][j - 1], prod2[i][j - 1]);
		}
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	int d = dep[u] - dep[v];
	for(int i = 0; i <= 20; i++) if(d >> i & 1) u = go[u][i];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--) if(go[u][i] != go[v][i]) u = go[u][i], v = go[v][i];
	return fa[u];
}
Matrix multiply1(int u, int d) {
	Matrix x = e;
	for(int i = 0; i <= 20; i++) if(d >> i & 1) x = mul(x, prod1[u][i]), u = go[u][i];
	return x;
}
Matrix multiply2(int u, int d) {
	Matrix x = e;
	for(int i = 0; i <= 20; i++) if(d >> i & 1) x = mul(prod2[u][i], x), u = go[u][i];
	return x;
}

int main() {
	// freopen("transmit.in", "r", stdin);
	// freopen("transmit.out", "w", stdout);
	scanf("%d%d%d", &n, &Q, &K);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1);
	for(int i = 0; i < K; i++) for(int j = 0; j < K; j++) e.a[i][j] = (i == j ? 0 : LLINF);
	for(int i = 0; i < K; i++) for(int j = 0; j < K; j++) initial.a[i][j] = LLINF;
	initial.a[0][K - 1] = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < K; j++) for(int k = 0; k < K; k++) trans[i].a[j][k] = LLINF;
		trans[i].a[0][0] = a[i];
		if(K >= 2) trans[i].a[0][1] = 0, trans[i].a[1][0] = a[i];
		if(K >= 3) trans[i].a[1][2] = 0, trans[i].a[2][0] = a[i], trans[i].a[1][1] = (son[i] ? a[son[i]] : LLINF);
	}
	preprocess();
	while(Q--) {
		int u, v;
		scanf("%d%d", &u, &v);
		int f = lca(u, v);
		int du = dep[u] - dep[f] + 1, dv = dep[v] - dep[f] + 1;
		LL ans = mul(initial, mul(multiply1(u, du), multiply2(v, dv - 1))).a[0][0];
		if(fa[f]) ans = std::min(ans, mul(initial, mul(multiply1(u, du + 1), multiply2(v, dv))).a[0][0]);
		printf("%lld\n", ans);
	}
	return 0;
} /*
7 100 3
1 2 3 4 5 6 7
1 2
1 3
2 4
2 5
3 6
3 7
4 7
5 6
1 2
*/
