#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

const int N = 2e5 + 5;
const int M = 4e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int al[N], ar[N];
std::vector<int> to[N];

struct DSU {
	int fa[N], sz[N];
	std::vector<std::pair<int, int>> ops;
	void init() { for(int i = 1; i <= 200000; i++) fa[i] = i, sz[i] = 1; }
	int find(int x) { return x == fa[x] ? x : find(fa[x]); }
	void merge(int x, int y) {
		x = find(x), y = find(y);
		if(x != y) {
			if(sz[y] < sz[x]) std::swap(x, y);
			fa[x] = y, sz[y] += sz[x], ops.push_back({x, y});
		} else ops.push_back({0, 0});
	}
	void undo() {
		int x = ops.back().first, y = ops.back().second;
		ops.pop_back();
		if(x == 0 && y == 0) return;
		fa[x] = x, sz[y] -= sz[x];
	}
} dsu;

int top[N];
std::vector<int> e[N * 20];
std::vector<std::pair<int, int>> ops;
bool key[N * 20];

int tot;
bool in[N];

struct CdqByTime {
	std::vector<int> t[N << 2];
	void insert(int ql, int qr, int qv, int x = 1, int l = 1, int r = 200000) {
		if(ql <= l && r <= qr) { t[x].push_back(qv); return; }
		int mid = (l + r) >> 1;
		if(ql <= mid) insert(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) insert(ql, qr, qv, x << 1 | 1, mid + 1, r);
	}
	void solve(int x = 1, int l = 1, int r = 200000) {
		int mid = (l + r) >> 1;
		int cnt = 0;
		for(int u : t[x]) {
			in[u] = true;
			// printf("insert %d\n", u);
			for(int v : to[u]) if(in[v]) {
				if(dsu.find(u) == dsu.find(v)) continue;
				// printf("merge %d %d\n", u, v);
				cnt++, tot++;
				e[tot].push_back(top[dsu.find(u)]), e[tot].push_back(top[dsu.find(v)]);
				if(key[top[dsu.find(u)]] || key[top[dsu.find(v)]]) key[tot] = true;
				dsu.merge(u, v);
				ops.push_back({dsu.find(u), top[dsu.find(u)]});
				top[dsu.find(u)] = tot;
			}
		}
		if(l < r) solve(x << 1, l, mid), solve(x << 1 | 1, mid + 1, r);
		for(int u : t[x]) in[u] = false;
		while(cnt--) {
			dsu.undo();
			top[ops.back().first] = ops.back().second;
			ops.pop_back();
		}
	}
} cdq;

int dis[N * 20];
void bfs() {
	std::queue<int> q;
	for(int i = 1; i <= tot; i++) dis[i] = INF;
	for(int i = 1; i <= tot; i++) if(key[i]) q.push(i), dis[i] = 0;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : e[u]) if(dis[v] == INF) {
			dis[v] = dis[u] + 1;
			q.push(v);
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d%d", &al[i], &ar[i]);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[u].push_back(v), to[v].push_back(u); }
	for(int i = 1; i <= n; i++) cdq.insert(al[i], ar[i], i);
	dsu.init();
	tot = n;
	for(int i = 1; i <= n; i++) top[i] = i;
	key[1] = true;
	cdq.solve();
	bfs();
	// printf("tot = %d\n", tot);
	// for(int i = 1; i <= tot; i++) for(int j : e[i]) printf("%d -> %d\n", i, j);
	for(int i = 1; i <= n; i++) if(dis[i] < INF) printf("%d ", i);
	puts("");
	return 0;
}