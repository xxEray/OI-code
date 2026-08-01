#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;
const int M = 6e5 + 5;
const LL MOD = 1e9 + 7;

int n, m;
struct Edge { int to, nxt; } edge[M];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int dfn[N], low[N], stk[N], bl[N], vis[N];
int scc, time_stamp, top;
void tarjan(int u) {
	low[u] = dfn[u] = ++time_stamp;
	stk[top++] = u;
	vis[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 0) tarjan(v), low[u] = std::min(low[u], low[v]);
	}
	if(dfn[u] == low[u]) {
		scc++;
		do {
			top--;
			vis[stk[top]] = 2;
			bl[stk[top]] = scc;
		} while(stk[top] != u);
	}
}

int mn[N], mx[N];

std::vector<int> to[N];
void dfs(int u) {
	if(vis[u]) return;
	vis[u] = 1;
	for(int v : to[u]) {
		dfs(v);
		mn[u] = std::min(mn[u], mn[v]), mx[u] = std::max(mx[u], mx[v]);
	}
}

int lb[N], rb[N];

struct SparseTable {
	int go[21][N];
	void init(int *arr) {
		for(int i = 1; i <= n; i++) go[0][i] = arr[i];
		for(int j = 1; j <= 20; j++)
			for(int i = 1; i + (1 << j) - 1 <= n; i++)
				go[j][i] = std::max(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
	}
	int max(int l, int r) {
		int k = 31 ^ __builtin_clz(r - l + 1);
		return std::max(go[k][l], go[k][r - (1 << k) + 1]);
	}
} ST;

int main() {
#ifndef DEBUG
	freopen("vis.in", "r", stdin);
	freopen("vis.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v); }
	for(int i = 1; i <= n; i++) if(!vis[i]) tarjan(i);
	for(int i = 1; i <= scc; i++) mn[i] = n + 1;
	for(int i = 1; i <= n; i++) mn[bl[i]] = std::min(mn[bl[i]], i), mx[bl[i]] = std::max(mx[bl[i]], i);
	for(int u = 1; u <= n; u++)
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(bl[u] != bl[v]) to[bl[u]].emplace_back(bl[v]);
		}
	for(int i = 1; i <= scc; i++) vis[i] = 0;
	for(int i = 1; i <= scc; i++) dfs(i);
	for(int i = 1; i <= n; i++) lb[i] = mn[bl[i]], rb[i] = mx[bl[i]];
	// for(int i = 1; i <= n; i++) printf("%d: lb=%d, rb=%d\n", i, lb[i], rb[i]);
	ST.init(rb);
	std::vector<int> vct;
	LL ans = 0;
	for(int i = 1; i <= n; i++) {
		assert(lb[lb[i]] == lb[i]);
		while(!vct.empty() && vct.back() > lb[i]) vct.pop_back();
		if(lb[i] == i) vct.emplace_back(i);
		int l = 0, r = (int)vct.size();
		while(l < r) {
			int mid = (l + r) >> 1;
			if(ST.max(vct[mid], i) <= i) r = mid;
			else l = mid + 1;
		}
		ans += (int)vct.size() - l;
	}
	printf("%lld\n", ans % MOD);
	return 0;
} /*
5 5
1 3
3 4
5 4
1 5
2 1
*/