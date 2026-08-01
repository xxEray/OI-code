#include <algorithm>
#include <cassert>
#include <cstdio>
#include <set>
typedef long long LL;
const int N = 5e5 + 5;
int a[N], fa[N];
LL b[N];
int n;
struct Node {
	LL sum, sz;
	int id;
};
bool operator<(Node x, Node y) { return x.sum * y.sz == y.sum * x.sz ? x.id < y.id : x.sum * y.sz < y.sum * x.sz; }
Node t[N];
std::set<Node> st;
struct Edge { int to, nxt; } edge[N << 1];
int head[N], ek = 1;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }
bool vis[N];
bool valid = true;
void dfs(int u) {
	if(vis[u]) {
		valid = false;
		return;
	}
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(v == fa[u]) continue;
		fa[v] = u;
		dfs(v);
	}
}
int ff[N];
int find(int x) { return x == ff[x] ? x : ff[x] = find(ff[x]); }
void merge(int x, int y) {
	x = find(x), y = find(y);
	if(x != y) ff[x] = y;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	for(int i = 1; i <= n; i++) add_edge(a[i], i);
	for(int i = 0; i <= n; i++) if(!vis[i]) dfs(i);
	if(!valid) return puts("-1"), 0;
	t[0].sz = 1;
	for(int i = 1; i <= n; i++) t[i] = (Node){b[i], 1, i}, st.insert(t[i]);
	for(int i = 1; i <= n; i++) ff[i] = i;
	LL ans = 0;
	while(!st.empty()) {
		int u = st.begin()->id;
		int f = find(fa[u]);
		st.erase(st.begin()), st.erase(t[f]);
		ans += t[u].sum * t[f].sz;
		t[f].sum += t[u].sum, t[f].sz += t[u].sz;
		merge(u, f);
		if(f) st.insert(t[f]);
	}
	printf("%lld\n", ans);
	return 0;
}