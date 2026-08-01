#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int n;

bool vis[N];
int size[N];
int root, rootwt, allsize;

void getroot(int u, int fa) {
	int mx = 0;
	size[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to] && edge[i].to != fa) {
		int v = edge[i].to;
		getroot(v, u);
		size[u] += size[v];
		mx = std::max(mx, size[v]);
	}
	mx = std::max(mx, allsize - size[u]);
	if(rootwt > mx) root = u, rootwt = mx;
}
int out[N];
void solve(int u) {
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		getroot(v, 0);
		rootwt = INF, allsize = size[v], getroot(v, 0), out[root] = u, solve(root);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	rootwt = INF, allsize = n, getroot(1, 0), out[root] = -1, solve(root);
	for(int i = 1; i <= n; i++) assert(out[i]), printf("%d ", out[i]);
	return 0;
} /*
4
1 2
2 3
3 4
*/