#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 1e5 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) {
	static int k = 1;
	edge[k] = (Edge){v, head[u]};
	head[u] = k++;
}
int n, m;

struct Segment {
	struct BIT {
		LL t[N];
		int size;
		inline int lowbit(int x) { return x & -x; }
		void add(int x, LL v) { while(x <= size) t[x] += v, x += lowbit(x); }
		LL query(int x) { LL ret = 0; while(x) ret += t[x], x -= lowbit(x); return ret; }
		void add(int x, int y, LL v) { add(x, v), add(y + 1, -v); }
	} t1, t2, t3; // t1 -> a^2, t2 -> a
	void modify_line(int l, int r, LL v) { v -= l, t1.add(l, r, v * v), t2.add(l, r, 2 * v), t3.add(l, r, 1); }
	LL query_line(int x) { return t1.query(x) + x * t2.query(x) + (LL)x * x * t3.query(x); }
} sg1, sg2; // sg1 -> 正, sg2 -> 反

int hson[N], fa[N], dep[N], size[N];
void dfs1(int u) {
	size[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa[u]) {
			int v = edge[i].to;
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dfs1(v);
			size[u] += size[v];
			if(hson[u] == 0 || size[v] > size[hson[u]]) hson[u] = v;
		}
}
int top[N], tol[N];
void dfs2(int u, int topf) {
	static int id = 0;
	tol[u] = ++id, top[u] = topf;
	if(hson[u]) dfs2(hson[u], topf);
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa[u] && edge[i].to != hson[u])
			dfs2(edge[i].to, edge[i].to);
}
int lca(int u, int v) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) std::swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
}
int dist(int u, int v) {
	if(dep[u] > dep[v]) std::swap(u, v);
	int l = lca(u, v);
	if(l == u) return dep[v] - dep[u];
	else return dep[u] + dep[v] - 2 * dep[l];
}
void modify(int u, int v, LL val) {
	int uu = u, vv = v;
	int len = dist(u, v);
	int flag = 1;
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) std::swap(u, v), flag = !flag;
		if(!flag) sg1.modify_line(tol[top[u]], tol[u], val + len - (dep[vv] - dep[top[u]]));
		else sg2.modify_line(n - tol[u] + 1, n - tol[top[u]] + 1, dep[uu] - dep[u]);
		u = fa[top[u]];
	}
	if(dep[u] > dep[v]) std::swap(u, v), flag = !flag;
	if(flag) sg1.modify_line(tol[u], tol[v], val + dep[uu] - dep[u]);
	else /* printf("u = %d, v = %d, val = %lld", tol[v], tol[u], val + len - dist(vv, v)),  */sg2.modify_line(n - tol[v] + 1, n - tol[u] + 1, val + len - dist(vv, v));
}
LL query(int x) { return sg1.query_line(tol[x]) + sg2.query_line(n - tol[x] + 1); }

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	sg1.t1.size = sg1.t2.size = sg1.t3.size = sg2.t1.size = sg2.t2.size = sg2.t3.size = n;
	dfs1(1);
	dfs2(1, 1);
	// for(int i = 1; i <= n; i++) printf("hson[%d] = %d, top = %d\n", i, hson[i], top[i]);
	scanf("%d", &m);
	while(m--) {
		int t, a, b;
		scanf("%d", &t);
		if(t == 1) {
			scanf("%d%d", &a, &b);
			modify(a, b, 1);
		} else if(t == 2) {
			scanf("%d", &a);
			printf("%lld\n", query(a));
		}
	}
	return 0;
} /*
3
1 2
2 3
5
1 1 2
2 1
1 2 1
2 2
2 3
*/