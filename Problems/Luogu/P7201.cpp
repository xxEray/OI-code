#include <bits/stdc++.h>

typedef long long LL;

const int N = 1000 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m, Q;
LL a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

bool vis[N];
void predfs(int u) {
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) predfs(edge[i].to);
}

void chkmin(LL &x, LL y) { if(x > y) x = y; }

int sz[N];
LL f[3][N][N];
LL tmp[3][N];
void dfs(int u, int fa) {
	sz[u] = 1;
	f[0][u][0] = 0, f[1][u][0] = LLINF, f[2][u][0] = a[u];
	f[0][u][1] = LLINF, f[1][u][1] = LLINF, f[2][u][1] = LLINF;
	for(int ei = head[u]; ei; ei = edge[ei].nxt) if(edge[ei].to != fa) {
		int v = edge[ei].to;
		dfs(v, u);
		for(int i = 0; i <= sz[u] + sz[v]; i++) tmp[0][i] = tmp[1][i] = tmp[2][i] = LLINF;
		for(int ou : {0, 1, 2}) for(int ov : {0, 1, 2})
			for(int i = 0; i <= sz[u]; i++)
				for(int j = 0; j <= sz[v]; j++)
					chkmin(tmp[ou == 2 && ov ? 1 : ou][i + j + (ou == 2 && ov) + (ou && ov == 2)], f[ou][u][i] + f[ov][v][j]);
		sz[u] += sz[v];
		for(int i = 0; i <= sz[u]; i++) f[0][u][i] = tmp[0][i], f[1][u][i] = tmp[1][i], f[2][u][i] = tmp[2][i];
	}
}

int ind[N];
LL val[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) if(!vis[i]) add_edge(0, i), add_edge(i, 0), predfs(i);
	dfs(0, -1);
	// for(int i = 0; i <= n; i++)
	// 	for(int j = 0; j <= sz[i]; j++)
	// 		printf("f[%d][%d]: %lld %lld %lld\n", i, j, f[0][i][j], f[1][i][j], f[2][i][j]);
	int c = 0;
	for(int i = 1; i <= n; i++) {
		while(c && val[c] >= f[0][0][i]) c--;
		val[++c] = f[0][0][i], ind[c] = i;
	}
	scanf("%d", &Q);
	while(Q--) {
		LL x;
		scanf("%lld", &x);
		int i = std::upper_bound(val + 1, val + c + 1, x) - val - 1;
		printf("%d\n", ind[i]);
	}
	return 0;
} /*
2 1
1 1
1 2
1
2
*/