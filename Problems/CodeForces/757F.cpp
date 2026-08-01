#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int M = 3e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m, st;
struct Edge { int to, nxt; LL w; } edge[M << 1];
int head[N];
void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

LL dis[N];
bool vis[N];
std::priority_queue<std::pair<LL, int>, std::vector<std::pair<LL, int>>, std::greater<std::pair<LL, int>>> q;
void dijkstra() {
	for(int i = 1; i <= n; i++) vis[i] = false, dis[i] = LLINF;
	dis[st] = 0, q.push({dis[st], st});
	while(!q.empty()) {
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(!vis[v] && dis[v] > dis[u] + edge[i].w) dis[v] = dis[u] + edge[i].w, q.push({dis[v], v});
		}
	}
}

std::vector<int> to[N], r[N], order;
int ind[N];
void toposort() {
	std::vector<int> vct;
	order.push_back(st), vct.push_back(st);
	while(!vct.empty()) {
		int u = vct.back();
		vct.pop_back();
		for(int v : to[u]) if(ind[v]) {
			ind[v]--;
			if(!ind[v]) order.push_back(v), vct.push_back(v);
		}
	}
}

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[y] = x : 0; }

int sz[N];

int main() {
	scanf("%d%d%d", &n, &m, &st);
	for(int i = 1; i <= m; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
	dijkstra();
	for(int u = 1; u <= n; u++) for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(dis[v] == dis[u] + edge[i].w) to[u].push_back(v), r[v].push_back(u), ind[v]++;
	}
	toposort();
	for(int i : order) fa[i] = i;
	for(int u : order) if(u != st) {
		std::set<int> e;
		for(int v : r[u]) e.insert(find(v));
		if(e.size() == 1 && *e.begin() != st) merge(*e.begin(), u);
	}
	for(int i : order) sz[find(i)]++;
	int ans = 0;
	for(int i : order) if(i != st) ans = std::max(ans, sz[i]);
	printf("%d\n", ans);
	return 0;
}