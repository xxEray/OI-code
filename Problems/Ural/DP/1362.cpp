#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 1e5 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) {
	static int k = 1;
	edge[k] = (Edge){v, head[u]};
	head[u] = k++;
}

int n, root;

int f[N];

bool cmp(int a, int b) { return a > b; }
void dfs(int u, int fa) {
	std::vector<int> list;
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa) {
			int v = edge[i].to;
			dfs(v, u);
			list.push_back(f[v]);
		}
	std::sort(list.begin(), list.end(), cmp);
	for(int i = 0; i < (int)list.size(); i++)
		f[u] = std::max(f[u], list[i] + i + 1);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int x;
		while(scanf("%d", &x) == 1 && x)
			add_edge(i, x), add_edge(x, i);
	}
	scanf("%d", &root);
	dfs(root, 0);
	// for(int i = 1; i <= n; i++) printf("f[%d] = %d\n", i, f[i]);
	printf("%d\n", f[root]);
	return 0;
}