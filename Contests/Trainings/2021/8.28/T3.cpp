#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n, mod;
struct Edge { int to, nxt, w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

bool vis[N];
int size[N], ans[N];
int root, rootwt, allsize;
void getroot(int u, int fa) {
	int mx = 0;
	size[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt)
		if(!vis[edge[i].to] && edge[i].to != fa) {
			int v = edge[i].to;
			getroot(v, u);
			size[u] += size[v];
			mx = std::max(mx, size[v]);
		}
	mx = std::max(mx, allsize - size[u]);
	if(mx < rootwt) root = u, rootwt = mx;
}

inline void updt(int &a, int b) { a = std::max(a, b); }

int d[N];
std::vector<int> g[N];
std::multiset<int> st;
int cnt;
void dfs(int u, int dis, int fa) {
	d[u] = dis, g[cnt].push_back(u);
	for(int i = head[u]; i; i = edge[i].nxt)
		if(!vis[edge[i].to] && edge[i].to != fa) {
			int v = edge[i].to;
			dfs(v, (dis + edge[i].w) % mod, u);
		}
}
void calc(int u) {
	// printf("calc %d\n", u);
	cnt = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		cnt++, g[cnt].clear();
		dfs(v, edge[i].w, 0);
	}
	st.clear();
	for(int i = 1; i <= cnt; i++) for(int v : g[i]) updt(ans[u], d[v]), updt(ans[v], d[v]), st.insert(d[v]);
	for(int i = 1; i <= cnt; i++) {
		for(int v : g[i]) st.erase(st.find(d[v]));
		for(int v : g[i]) {
			auto it = st.upper_bound(mod - d[v] - 1);
			if(it == st.begin()) continue;
			it--;
			updt(ans[v], (d[v] + *it) % mod);
		}
		for(int v : g[i]) st.insert(d[v]);
	}
}

void solve(int u) {
	vis[u] = true, calc(u);
	for(int i = head[u]; i; i = edge[i].nxt)
		if(!vis[edge[i].to]) {
			int v = edge[i].to;
			rootwt = INF, allsize = size[v], getroot(v, 0), solve(root);
		}
}

int main() {
	scanf("%d%d", &n, &mod);
	for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
	rootwt = INF, allsize = n, getroot(1, 0), solve(root);
	for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
} /*
5 16
1 2 13
2 3 15
3 4 7
3 5 3
*/