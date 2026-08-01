#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

struct Node {
	LL mx, cnt;
	Node() : mx(-LLINF), cnt(0) {}
	Node(LL mx_, LL cnt_) : mx(mx_), cnt(cnt_) {}
};
Node operator+(const Node &x, const int &y) { return Node(x.mx + y, x.cnt); }
Node calc(const Node &x, const Node &y) {
	Node z;
	z.mx = std::max(x.mx, y.mx);
	z.cnt = (x.mx == z.mx) * x.cnt + (y.mx == z.mx) * y.cnt;
	return z;
}
Node ans(0, 1);
Node f[N], g[N];
void dfs(int u, int fa) {
	bool leaf = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		leaf = false;
		dfs(v, u);
		f[u] = calc(f[u], f[v] + 1);
	}
	if(leaf) f[u] = Node(0, 1);
}
void dfs2(int u, int fa) {
	std::vector<int> son = {0};
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) son.emplace_back(edge[i].to);
	int sz = son.size() - 1;
	if(!fa && sz == 1) g[u] = Node(0, 1);
	std::vector<Node> pre(sz + 2), suf(sz + 2);
	for(int i = 1; i <= sz; i++) pre[i] = calc(pre[i - 1], f[son[i]] + 1);
	for(int i = sz; i >= 1; i--) suf[i] = calc(suf[i + 1], f[son[i]] + 1);
	for(int i = 1; i <= sz; i++) g[son[i]] = calc(g[u], calc(pre[i - 1], suf[i + 1])) + 1;
	for(int i = 1; i <= sz; i++) dfs2(son[i], u);
}
LL C2(LL x) { return x * (x - 1) / 2; }
void dfs3(int u, int fa) {
	std::vector<std::pair<int, int>> vct;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs3(v, u);
		vct.emplace_back(f[v].mx + 1, f[v].cnt);
	}
	if(u != 1) vct.emplace_back(g[u].mx, g[u].cnt);
	if(vct.size() >= 3) {
		std::sort(vct.begin(), vct.end(), std::greater<>());
		while(vct.back().first < vct[2].first) vct.pop_back();
		LL sum = 0, sum2 = 0;
		for(auto [_, v] : vct) sum += v, sum2 += (LL)v * v;
		if(vct[0].first == vct[2].first) ans = calc(ans, Node((LL)(vct[1].first + vct[2].first) * vct[0].first, (sum * sum - sum2) / 2));
		else if(vct[0].first == vct[1].first) ans = calc(ans, Node((LL)(vct[1].first + vct[2].first) * vct[0].first, (vct[0].second + vct[1].second) * (sum - vct[0].second - vct[1].second)));
		else if(vct[1].first == vct[2].first) ans = calc(ans, Node((LL)(vct[1].first + vct[2].first) * vct[0].first, ((sum - vct[0].second) * (sum - vct[0].second) - (sum2 - (LL)vct[0].second * vct[0].second)) / 2));
		else ans = calc(ans, Node((LL)(vct[1].first + vct[2].first) * vct[0].first, vct[1].second * (sum - vct[0].second - vct[1].second)));
		// printf("%d: ans = %lld,%lld\n", u, ans.mx, ans.cnt);
	}
}

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0), dfs2(1, 0), dfs3(1, 0);
	// for(int i = 1; i <= n; i++) printf("[%d] f: mx=%lld, cnt=%lld   g: mx=%lld, cnt=%lld\n", i, f[i].mx, f[i].cnt, g[i].mx, g[i].cnt);
	printf("%lld %lld\n", ans.mx, ans.cnt);
	return 0;
}