#include <cstdio>
#include <algorithm>
#include <set>
#include <cassert>

const int N = 1e5 + 5;

int n, K;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }


int fa[N], dep[N], sz[N], dfn[N];
struct CompareDep { bool operator()(int x, int y) const { return dep[x] == dep[y] ? x < y : dep[x] < dep[y]; } };
struct CompareDfn { bool operator()(int x, int y) const { return dfn[x] == dfn[y] ? x < y : dfn[x] < dfn[y]; } };
std::set<int, CompareDep> stdep;
std::set<int, CompareDfn> stdfn;
int time_stamp = 0;
void dfs(int u) {
	dfn[u] = ++time_stamp;
	sz[u] = 1;
	bool son = false;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		son = true;
		int v = edge[i].to;
		fa[v] = u, dep[v] = dep[u] + 1;
		dfs(v);
		sz[u] += sz[v];
	}
	if(!son) stdep.insert(u), stdfn.insert(u);
}

int go[21][N];
void preprocess() {
	for(int i = 1; i <= n; i++) go[0][i] = fa[i];
	for(int j = 1; j <= 20; j++) for(int i = 1; i <= n; i++) go[j][i] = go[j - 1][go[j - 1][i]];
}

int main() {
	// freopen("atlarge.in", "r", stdin);
	// freopen("atlarge.out", "w", stdout);
	scanf("%d%d", &n, &K);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	if(!head[K] || !edge[head[K]].nxt) { puts("1"); return 0; }
	dfs(K);
	preprocess();
	int ans = 0;
	while(!stdep.empty()) {
		ans++;
		int u = *stdep.begin();
		stdep.erase(u), stdfn.erase(u);
		int step = dep[u] / 2;
		for(int j = 0; j <= 20; j++) if(step >> j & 1) u = go[j][u];
		int r = dfn[u] + sz[u] - 1;
		while(true) {
			auto it = stdfn.lower_bound(u);
			if(it != stdfn.end() && dfn[*it] <= r) stdep.erase(*it), stdfn.erase(*it);
			else break;
		}
		for(int v : stdep) assert(!(dfn[u] <= dfn[v] && dfn[v] <= dfn[u] + sz[u] - 1));
	}
	printf("%d\n", ans);
	return 0;
}