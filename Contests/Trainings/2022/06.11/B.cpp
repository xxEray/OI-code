#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

const int N = 1e5 + 5;

struct Edge { int to, nxt, w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}; }
int n, m, Q, rt, e, mod;

int type[N];
std::vector<int> ws;

int main() {
	scanf("%d%d%d%d%d", &n, &m, &Q, &rt, &e);
	if(e) scanf("%d", &mod);
	for(int i = 1; i <= n; i++) scanf("%d", &type[i]);
	for(int i = 1; i <= m; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); ws.push_back(w); }
	
	return 0;
}