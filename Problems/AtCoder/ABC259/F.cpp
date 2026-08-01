#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 3e5 + 5;

int a[N];
int n;

struct Edge { int to, nxt; LL w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

LL f[N][2];

void dfs(int u, int fa) {
	std::vector<LL> arr;
	LL base = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		base += f[v][0];
		if(a[v] >= 1) arr.push_back(f[v][1] + edge[i].w - f[v][0]);
	}
	std::sort(arr.begin(), arr.end(), [](int x, int y) { return x > y; });
	f[u][0] = f[u][1] = base;
	for(int i = 0; i < (int)arr.size() && i < a[u] && arr[i] > 0; i++) f[u][0] += arr[i];
	for(int i = 0; i < (int)arr.size() && i < a[u] - 1 && arr[i] > 0; i++) f[u][1] += arr[i];
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) {
		int u, v; LL w;
		scanf("%d%d%lld", &u, &v, &w);
		add_edge(u, v, w), add_edge(v, u, w);
	}
	dfs(1, 0);
	// for(int i = 1; i <= n; i++) printf("f[%d] = %d, %d\n", i, f[i][0], f[i][1]);
	printf("%lld\n", f[1][0]);
	return 0;
}