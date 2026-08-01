#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>

const int N = 1e5 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N], edgek;
void add_edge(int u, int v) {
	edge[edgek] = (Edge){v, head[u]};
	head[u] = edgek++;
}
int n, m;

bool is_line; // 是否为链
int fa[N], dep[N];
void dfs(int u) {
	int cnt = 0;
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa[u]) {
			int v = edge[i].to;
			cnt++;
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dfs(v);
		}
	if(cnt > 1) is_line = false;
}

namespace SolveLine {
	int id;
	int tol[N];
	void get_new_id(int x) {
		tol[x] = ++id;
		for(int i = head[x]; i; i = edge[i].nxt) if(edge[i].to != fa[x]) get_new_id(edge[i].to);
	}
	struct SegmentTree {
		int t[N << 2], lazy[N << 2], size;
		void set_lazy(int x, int v, int len) {
			t[x] = v * len;
			lazy[x] = v;
		}
		void lazy_down(int x, int l, int r) {
			if(lazy[x] == -1) return;
			int mid = (l + r) >> 1;
			set_lazy(x << 1, lazy[x], mid - l + 1);
			set_lazy(x << 1 | 1, lazy[x], r - mid);
			lazy[x] = -1;
		}
		void modify_(int ql, int qr, int qv, int x, int l, int r) {
			if(ql <= l && r <= qr) { set_lazy(x, qv, r - l + 1); return; }
			lazy_down(x, l, r);
			int mid = (l + r) >> 1;
			if(ql <= mid) modify_(ql, qr, qv, x << 1, l, mid);
			if(qr > mid) modify_(ql, qr, qv, x << 1 | 1, mid + 1, r);
			t[x] = t[x << 1] + t[x << 1 | 1];
		}
		int query_(int ql, int qr, int x, int l, int r) {
			if(ql <= l && r <= qr) return t[x];
			lazy_down(x, l, r);
			int mid = (l + r) >> 1, ret = 0;
			if(ql <= mid) ret += query_(ql, qr, x << 1, l, mid);
			if(qr > mid) ret += query_(ql, qr, x << 1 | 1, mid + 1, r);
			return ret;
		}
		void modify_set(int l, int r, int v) { l <= r ? modify_(l, r, v, 1, 1, size) : (void)0; }
		int query_sum(int l, int r) { return l <= r ? query_(l, r, 1, 1, size) : 0; }
	} seg;
	void main() {
		id = 0;
		for(int i = 1; i <= n; i++) if(fa[i] == 0) get_new_id(i);
		memset(seg.t, 0, sizeof(seg.t));
		memset(seg.lazy, -1, sizeof(seg.lazy));
		seg.size = n;
		while(m--) {
			int t, a, b;
			scanf("%d%d%d", &t, &a, &b);
			if(tol[a] > tol[b]) std::swap(a, b);
			if(t == 1) {
				if(tol[a] != 1) seg.modify_set(tol[a] - 1, tol[a] - 1, 0);
				if(tol[b] != n) seg.modify_set(tol[b], tol[b], 0);
				seg.modify_set(tol[a], tol[b] - 1, 1);
			} else printf("%d\n", seg.query_sum(tol[a], tol[b] - 1));
		}
	}
}

namespace SolveOther {
	int go[N][21];
	std::set<int> to[N];
	void preprocessLCA() {
		for(int i = 1; i <= n; i++) go[i][0] = fa[i];
		for(int j = 1; j <= 20; j++)
			for(int i = 1; i <= n; i++)
				go[i][j] = go[go[i][j - 1]][j - 1];
	}
	int LCA(int u, int v) {
		if(dep[u] < dep[v]) std::swap(u, v);
		for(int i = 0; i <= 20; i++)
			if((dep[u] - dep[v]) & (1 << i))
				u = go[u][i];
		if(u == v) return u;
		for(int i = 20; i >= 0; i--)
			if(go[u][i] != go[v][i])
				u = go[u][i], v = go[v][i];
		return fa[u];
	}
	void main() {
		preprocessLCA();
		for(int i = 1; i <= n; i++) to[i].clear();
		while(m--) {
			int t, u, v;
			scanf("%d%d%d", &t, &u, &v);
			// for(int i = 1; i <= n; i++)
			// 	for(int j : to[i])
			// 		if(i <= j)
			// 			printf("%d <-> %d\n", i, j);
			if(t == 1) {
				int lca = LCA(u, v);
				int uu = u, vv = v;
				for(; u != lca; u = fa[u]) {
					for(auto it = to[u].begin(); it != to[u].end(); it++) to[*it].erase(u);
					to[u].clear();
				}
				for(; v != lca; v = fa[v]) {
					for(auto it = to[v].begin(); it != to[v].end(); it++) to[*it].erase(v);
					to[v].clear();
				}
				for(auto it = to[lca].begin(); it != to[lca].end(); it++) to[*it].erase(lca);
				to[lca].clear();
				for(u = uu; u != lca; u = fa[u]) to[u].insert(fa[u]), to[fa[u]].insert(u);
				for(v = vv; v != lca; v = fa[v]) to[v].insert(fa[v]), to[fa[v]].insert(v);
			} else {
				int cnt = 0, lca = LCA(u, v);
				for(; u != lca; u = fa[u]) if(to[u].find(fa[u]) != to[u].end()) cnt++;
				for(; v != lca; v = fa[v]) if(to[v].find(fa[v]) != to[v].end()) cnt++;
				printf("%d\n", cnt);
			}
		}
	}
}

int main() {
// #ifndef DEBUG
	freopen("edge.in", "r", stdin);
	freopen("edge.out", "w", stdout);
// #endif
	int T;
	scanf("%d", &T);
	while(T--) {
		memset(head, 0, sizeof(head));
		memset(dep, 0, sizeof(dep));
		edgek = 1;
		scanf("%d%d", &n, &m);
		for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
		is_line = true;
		dfs(1);
		if(is_line) SolveLine::main();
		else SolveOther::main();
	}
	return 0;
} /*
1
3 100
1 2
2 3

*/