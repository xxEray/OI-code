#include <cstdio>
#include <algorithm>

const int N = 6000 + 5;
const int INF = 0x3f3f3f3f;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) {
	static int k = 1;
	edge[k] = (Edge){v, head[u]};
	head[u] = k++;
}

int a[N];
int n;

int f[N][2];

void dfs(int u, int fa) {
	f[u][0] = 0, f[u][1] = std::max(a[u], 0);
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa) {
			int v = edge[i].to;
			dfs(v, u);
			f[u][1] += f[v][0];
			f[u][0] += std::max(f[v][0], f[v][1]);
		}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	while(true) {
		int u, v;
		scanf("%d%d", &u, &v);
		if(!u && !v) break;
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs(1, 0);
	// for(int i = 1; i <= n; i++) printf("f[%d] = {%d, %d}\n", i, f[i][0], f[i][1]);
	printf("%d\n", std::max(f[1][0], f[1][1]));
	return 0;
}