#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
LL a[N];
struct Edge { int to, nxt; LL w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

int sz[N], vis[N], allsize, rootwt, root;
void getroot(int u, int fa) {
	int mx = 0;
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && !vis[edge[i].to]) {
		int v = edge[i].to;
		getroot(v, u);
		mx = std::max(mx, sz[v]);
		sz[u] += sz[v];
	}
	mx = std::max(mx, allsize - sz[u]);
	if(mx < rootwt) rootwt = mx, root = u;
}
LL ans;
std::map<LL, int> mp1, mp2;
void dfs1(int u, int fa, LL val, LL mn, int type) {
	mp1[-mn] += type;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && !vis[edge[i].to]) {
		int v = edge[i].to;
		LL val2 = val + a[u] - edge[i].w;
		dfs1(v, u, val2, std::min(mn, val2), type);
	}
}
void dfs2(int u, int fa, LL val, LL mn, int type) {
	if(mn >= 0) mp2[val] += type;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && !vis[edge[i].to]) {
		int v = edge[i].to;
		LL val2 = a[v] - edge[i].w + val;
		dfs2(v, u, val2, std::min(mn + a[v] - edge[i].w, 0LL), type);
	}
}
void calc(int u) {
	// printf("calc %d\n", u);
	dfs1(u, 0, 0, 0, 1);
	ans += mp1[0] - 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		dfs1(v, u, a[u] - edge[i].w, std::min(a[u] - edge[i].w, 0LL), -1);
		dfs2(v, u, a[v] - edge[i].w, std::min(a[v] - edge[i].w, 0LL), 1);
		// printf("  v = %d\n", v);
		// printf("    mp1: "); for(auto [x, y] : mp1) if(y) printf("(%lld, %d) ", x, y); puts("");
		// printf("    mp2: "); for(auto [x, y] : mp2) if(y) printf("(%lld, %d) ", x, y); puts("");
		LL sum = 0;
		for(auto it1 = mp1.rbegin(), it2 = mp2.rbegin(); it1 != mp1.rend(); ++it1) {
			while(it2 != mp2.rend() && it2->first >= it1->first) sum += it2->second, it2++;
			ans += sum * it1->second;
		}
		// printf("  ans = %lld\n", ans);
		dfs2(v, u, a[v] - edge[i].w, std::min(a[v] - edge[i].w, 0LL), -1);
		dfs1(v, u, a[u] - edge[i].w, std::min(a[u] - edge[i].w, 0LL), 1);
	}
	mp1.clear(), mp2.clear();
}
void solve(int u) {
	calc(u);
	vis[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		getroot(v, u);
		allsize = sz[v], rootwt = INF, getroot(v, u), solve(root);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i < n; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
	allsize = n, rootwt = INF, getroot(1, 0), solve(root);
	printf("%lld\n", ans);
	return 0;
}