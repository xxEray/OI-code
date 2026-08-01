#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int in[N], ind[N], oud[N];
int n, m;

int f[N];

std::vector<int> stk;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), ind[v]++, oud[u]++; }
	for(int i = 1; i <= n; i++) f[i] = 1, in[i] = ind[i];
	for(int i = 1; i <= n; i++) if(!in[i]) stk.push_back(i);
	while(!stk.empty()) {
		int u = stk.back();
		stk.pop_back();
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			in[v]--;
			if(!in[v]) stk.push_back(v);
			if(oud[u] != 1 && ind[v] != 1) f[v] = std::max(f[v], f[u] + 1);
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) ans = std::max(ans, f[i]);
	printf("%d\n", ans);
	return 0;
}