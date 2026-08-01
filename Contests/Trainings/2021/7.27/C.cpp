#include <cstdio>
#include <algorithm>

const int N = 10 + 3;
const int INF = 0x3f3f3f3f;

int w[N], d[N];
int n;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) {
	static int k = 1;
	edge[k] = (Edge){v, head[u]};
	head[u] = k++;
}

int belong[N], go[N][21], p[N], ans[N], ret[N];

void dfs(int u) {
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != go[u][0]) {
			int v = edge[i].to;
			go[v][0] = u;
			d[v] = d[u] + 1;
			dfs(v);
		}
}

void preprocess() {
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n; i++)
			go[i][j] = go[go[i][j - 1]][j - 1];
}
int LCA(int u, int v) {
	if(d[u] < d[v]) std::swap(u, v);
	for(int i = 0; i <= 20; i++)
		if((d[u] - d[v]) & (1 << i))
			u = go[u][i];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--)
		if(go[u][i] != go[v][i])
			u = go[u][i], v = go[v][i];
	return go[u][0];
}

int getval() {
	int val = 0;
	for(int i = 1; i <= n; i++) if(belong[i]) val += d[i];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			if(i == j || belong[i] != belong[j]) continue;
			int lca = LCA(i, j);
			// printf("LCA %d %d = %d\n", i, j, lca);
			if(belong[i]) {
				if((lca == i && w[i] > w[j]) || (i < j && lca != i && lca != j)) val++;
			} else {
				if(lca == i && w[i] < w[j]) val++;
			}
		}
	return val;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &w[i]);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v); add_edge(v, u); }
	for(int i = 1; i <= n; i++) p[i] = i;
	ans[0] = INF;
	dfs(1);
	preprocess();
	do {
		for(int i = 1; i <= n; i++) belong[i] = true;
		int updt = -1;
		for(int i = 0; i <= n; i++) {
			if(i) belong[p[i]] = false;
			ret[i] = getval();
			if(ret[i] > ans[i] && updt == -1) { updt = 0; break; }
			else if(ret[i] < ans[i]) updt = 1;
		}
		if(updt == 1) for(int i = 0; i <= n; i++) ans[i] = ret[i];
	} while(std::next_permutation(p + 1, p + n + 1));
	for(int i = 0; i <= n; i++) printf("%d ", ans[i]);
	return 0;
}