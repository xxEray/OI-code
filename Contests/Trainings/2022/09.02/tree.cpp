#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int e[N][3], eid[N];

int fa[N], dep[N], go[N][21];
void dfs(int u) {
	dep[u] = dep[fa[u]] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		dfs(v);
	}
}

void preprocess() {
	for(int i = 1; i <= n; i++) go[i][0] = fa[i];
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n; i++)
			go[i][j] = go[go[i][j - 1]][j - 1];
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	for(int i = 0; i <= 20; i++) if((dep[u] - dep[v]) >> i & 1) u = go[u][i];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--) if(go[u][i] != go[v][i]) u = go[u][i], v = go[v][i];
	return fa[u];
}

struct DSU {
private:
	int fa[N];
public:
	void init() { for(int i = 1; i <= n; i++) fa[i] = i; }
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[y] = x : 0; }
} dsu;

int out[N];

std::vector<int> vct;

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	// freopen("D:\\Useless\\Temp\\down\\tree\\ex_A2.in", "r", stdin);
	// freopen("D:\\Useless\\Temp\\down\\tree\\ex_A2.myout", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%d%d%d", &e[i][0], &e[i][1], &e[i][2]);
	for(int i = 1; i <= m; i++) if(e[i][2]) add_edge(e[i][0], e[i][1]), add_edge(e[i][1], e[i][0]);
	dfs(1);
	for(int i = 1; i <= m; i++) if(e[i][2]) {
		if(fa[e[i][0]] == e[i][1]) eid[e[i][0]] = i;
		else eid[e[i][1]] = i;
	}
	dsu.init(), preprocess();
	int c = 0;
	for(int i = 1; i <= m; i++) {
		if(out[i]) continue;
		int p = lca(e[i][0], e[i][1]);
		int j = dsu.find(e[i][0]);
		while(j != dsu.find(p)) {
			vct.push_back(eid[j]);
			dsu.merge(fa[j], j);
			j = dsu.find(j);
		}
		j = dsu.find(e[i][1]);
		while(j != dsu.find(p)) {
			vct.push_back(eid[j]);
			dsu.merge(fa[j], j);
			j = dsu.find(j);
		}
		std::sort(vct.begin(), vct.end());
		for(int x : vct) out[x] = ++c;
		vct.clear();
		if(!e[i][2]) out[i] = ++c;
	}
	for(int i = 1; i <= m; i++) printf("%d ", out[i]);
	puts("");
	return 0;
} /*
4 5
1 2 0
2 3 1
3 4 1
2 4 0
1 3 1
*/