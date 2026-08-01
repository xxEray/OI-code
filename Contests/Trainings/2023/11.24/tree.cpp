#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const int M = 5e5 + 5;

int n, m;
LL a[N];
struct Edge { int to, nxt, w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }
struct Query { int l, r, id; } q[M];
bool operator<(const Query &x, const Query &y) { return x.l > y.l; }

LL tmp[N];
void discrete() {
	int c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = a[i];
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i] = std::lower_bound(tmp + 1, tmp + c + 1, a[i]) - tmp;
}

int sz[N];
void predfs(int u, int fa) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		a[v] = a[u] + edge[i].w;
		predfs(v, u);
	}
}

std::set<int> st[N];
std::vector<std::pair<int, int>> vct[N];
void dfs(int u, int fa) {
	st[u].emplace(u);
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		if(st[v].size() > st[u].size()) st[u].swap(st[v]);
		for(auto x : st[v]) {
			auto it = st[u].lower_bound(x);
			if(it != st[u].end()) vct[x].emplace_back(a[u], *it);
			if(it != st[u].begin()) vct[*std::prev(it)].emplace_back(a[u], x);
		}
		for(auto x : st[v]) st[u].emplace(x);
		st[v].clear();
	}
}

struct BIT {
	int t[N];
	void add_(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	void add(int l, int r, int v) { add_(l, v), add_(r + 1, -v); }
} bit;

int mn[N], out[M];

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
	for(int i = 1; i <= m; i++) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	std::sort(q + 1, q + m + 1);
	predfs(1, 0);
	discrete();
	dfs(1, 0);
	for(int i = 1; i <= n; i++) vct[i].emplace_back(a[i], i);
	for(int i = 1; i <= n; i++) mn[i] = n + 1;
	for(int i = n, j = 1; i >= 1; i--) {
		// printf("%d: ", i); for(auto [c, y] : vct[i]) printf("(c=%d,y=%d) ", c, y); puts("");
		for(auto [c, y] : vct[i]) if(mn[c] > y) bit.add(y, mn[c] - 1, 1), mn[c] = y;
		while(j <= m && q[j].l == i) out[q[j].id] = bit.query(q[j].r), j++;
	}
	for(int i = 1; i <= m; i++) printf("%d\n", out[i]);
	return 0;
} /*
10 19
9 1 -4
9 8 2
8 10 5
9 7 -3
1 4 2
10 2 5
10 5 -1
7 3 -3
10 6 5
8 10
4 6
1 7
7 9
5 5
7 8
8 10
10 10
10 10
9 10
5 7
8 8
6 6
2 8
9 10
4 8
5 5
1 6
1 2
*/