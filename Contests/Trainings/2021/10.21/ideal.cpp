#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 2000 + 5;
const int M = 5000 + 5;
const int INF = 0x3f3f3f3f;

struct Graph {
	struct Edge { int to, nxt; } edge[M];
	int head[N], ek;
	void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }
	Graph() : ek(1) {}
} G, R;
int n, m, Q;

int go[N][N][12], f[N][N];
bool ok[N];
int vis[N];
int stk[N], top;
void dfs(int st, int u) {
	if(!u) return;
	if(vis[u] == 2) return;
	if(u == st) { vis[u] = 2, f[st][u] = 0; return; }
	vis[u] = 1;
	if(vis[go[st][u][0]] == 1) { f[st][u] = INF; vis[u] = 2; return; }
	else if(!go[st][u][0]) { f[st][u] = 0; vis[u] = 2; return; }
	dfs(st, go[st][u][0]), f[st][u] = f[st][go[st][u][0]] + 1;
	vis[u] = 2;
}

int q[N];
void updt(int &x, int y) { if(!x || x > y) x = y; }
void solve(int st) {
//	printf("solve %d\n", st);
	int hd = 0, tl = 0;
	for(int i = 1; i <= n; i++) ok[i] = false;
	q[tl++] = st, ok[st] = true;
	while(hd < tl) {
		int u = q[hd++];
		for(int i = R.head[u]; i; i = R.edge[i].nxt) {
			int v = R.edge[i].to;
			if(!ok[v]) ok[v] = true, q[tl++] = v;
		}
	}
	for(int i = 1; i <= n; i++)
		for(int j = G.head[i]; j; j = G.edge[j].nxt)
			if(ok[G.edge[j].to]) updt(go[st][i][0], G.edge[j].to);
	// go[st][st][0] = st;
//	for(int i = 1; i <= n; i++) printf("%d: ok[%d] = %d, go[%d] = %d\n", st, i, ok[i], i, go[st][i][0]);
	for(int i = 0; i <= n + 1; i++) vis[i] = 0;
	for(int i = 1; i <= n; i++) if(!vis[i]) top = 0, dfs(st, i);
}

int main() {
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		G.add_edge(u, v), R.add_edge(v, u);
	}
	for(int i = 1; i <= n; i++) solve(i);
	for(int i = 1; i <= n; i++)
		for(int k = 1; k <= 11; k++)
			for(int j = 1; j <= n; j++)
				go[i][j][k] = go[i][go[i][j][k - 1]][k - 1];
	while(Q--) {
		int s, t, k;
		scanf("%d%d%d", &s, &t, &k); k--;
		if(s == t) { printf("%d\n", k == 0 ? s : -1); continue; }
		if(f[t][s] >= INF || f[t][s] == 0 || k > f[t][s]) { puts("-1"); continue; }
		int r = s;
		for(int i = 0; i <= 11; i++) if(k >> i & 1) r = go[t][r][i];
		printf("%d\n", r);
	}
	return 0;
} /*
7 7 5
1 2
2 3
1 3
3 4
4 5
5 3
4 6
1 4 2
2 6 1
1 7 3
1 3 2
1 3 5
*/