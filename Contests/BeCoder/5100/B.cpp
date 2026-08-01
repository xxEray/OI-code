#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include <bits/stdc++.h>

#define msg(...) fprintf(stderr, __VA_ARGS__)

typedef long long LL;

const int N = 1e5 + 5;
const int LOG_N = 17;
const int INF = 0x3f3f3f3f;
constexpr int D = 4160;

int n;
LL a[N];
std::vector<std::pair<int, LL>> tree[N];

struct Edge { int to, nxt; } edge[N * LOG_N * 3 + N];
int head[N * LOG_N * 2];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int tot;

int vis[N * LOG_N * 2], sz[N];
int root, rootwt, allsize;
void getroot(int u, int fa) {
	int mx = 0;
	sz[u] = 1;
	for(auto [v, _] : tree[u]) if(!vis[v] && v != fa) {
		getroot(v, u);
		sz[u] += sz[v];
		mx = std::max(mx, sz[v]);
	}
	mx = std::max(mx, allsize - sz[u]);
	if(mx < rootwt) rootwt = mx, root = u;
}
void dfs(int u, int fa, LL dep, const std::function<void(int, LL)> &func) {
	func(u, dep);
	for(auto [v, w] : tree[u]) if(!vis[v] && v != fa) dfs(v, u, dep + w, func);
}
void calc(int rt) {
	std::vector<std::pair<LL, int>> vct;
	dfs(rt, 0, 0, [&](int u, LL dep) {
		int id = ++tot;
		vct.emplace_back(dep, id);
		add_edge(id, u);
	});
	std::sort(vct.begin(), vct.end());
	assert(vct[0].first == 0);
	for(int i = (int)vct.size() - 1; i >= 1; i--) add_edge(vct[i].second, vct[i - 1].second);
	dfs(rt, 0, 0, [&](int u, LL dep) {
		if(a[u] < dep) return;
		int idx = std::upper_bound(vct.begin(), vct.end(), std::make_pair(a[u] - dep, INF)) - vct.begin() - 1;
		assert(idx >= 0);
		add_edge(u, vct[idx].second);
	});
}
void solve(int u) {
	calc(u);
	vis[u] = true;
	for(auto [v, _] : tree[u]) if(!vis[v]) {
		getroot(v, 0), allsize = sz[v], rootwt = INF, getroot(v, 0), solve(root);
	}
}

int dfn[N * LOG_N * 2], low[N * LOG_N * 2], stk[N * LOG_N * 2], bl[N * LOG_N * 2];
int time_stamp, top, scc;
void tarjan(int u) {
	low[u] = dfn[u] = ++time_stamp;
	stk[top++] = u;
	vis[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(!vis[v]) tarjan(v), low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
	}
	if(low[u] == dfn[u]) {
		scc++;
		do {
			top--;
			vis[stk[top]] = 2;
			bl[stk[top]] = scc;
		} while(stk[top] != u);
	}
}

uint64_t bs[N * LOG_N][D / 64];
std::vector<int> to[N * LOG_N * 2];

int ans[N];

int main() {
#ifdef DEBUG
	freopen("/home/eray/Downloads/min10p.in", "r", stdin);
	freopen("/home/eray/Downloads/min10p.out", "w", stdout);
#endif
	// fprintf(stderr, "size = %.3f\n", sizeof(bs) / 1024. / 1024);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i < n; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); tree[u].emplace_back(v, w), tree[v].emplace_back(u, w); }
	tot = n;
	allsize = n, rootwt = INF, getroot(1, 0), solve(root);
	for(int i = 1; i <= tot; i++) vis[i] = 0;
	for(int i = 1; i <= tot; i++) if(!vis[i]) tarjan(i);
	// for(int u = 1; u <= tot; u++) for(int i = head[u]; i; i = edge[i].nxt) msg("%d -> %d\n", u, edge[i].to);
	// msg("bl: "); for(int i = 1; i <= n; i++) msg("%d ", bl[i]); msg("\n");
	for(int u = 1; u <= tot; u++) for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(bl[u] != bl[v]) to[bl[u]].emplace_back(bl[v]);
	}
	for(int i = 1; i <= scc; i++) {
		std::sort(to[i].begin(), to[i].end());
		to[i].erase(std::unique(to[i].begin(), to[i].end()), to[i].end());
		// for(int j : to[i]) msg("%d -> %d\n", i, j);
	}
	// fprintf(stderr, "clock = %.3f\n", (double)clock() / CLOCKS_PER_SEC);
	for(int d = 1; d <= n; d += D) {
		memset((uint64_t *)bs + D / 64, 0, scc * (D / 8));
		int ed = std::min(n, d + D - 1) - d;
		for(int i = 0; i <= ed; i++) bs[bl[i + d]][i >> 6] |= 1LL << (i & 63);
		for(int i = 1; i <= scc; i++) for(int j : to[i]) {
			#pragma GCC unroll(16)
			for(int k = 0; k < D / 64; k++) bs[i][k] |= bs[j][k];
		}
		for(int i = 1; i <= n; i++) {
			#pragma GCC unroll(16)
			for(int k = 0; k < D / 64; k++) ans[i] += __builtin_popcountll(bs[bl[i]][k]);
		}
	}
	for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
	puts("");
	return 0;
}