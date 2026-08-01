#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = 2e5 + 5;

struct Edge  { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int n;

struct DP {
	int ans, sum;
	DP &operator+=(DP x) { ans += x.ans, sum += x.sum; return *this; }
};
DP operator+(DP x, DP y) { return {x.ans + y.ans, x.sum + y.sum}; }
bool operator<(DP x, DP y) { return x.ans == y.ans ? x.sum > y.sum : x.ans < y.ans; }
DP f[N][2];
int w[N];
void dfs(int u, int fa) {
	f[u][0] = {0, 1}, f[u][1] = {1, 0};
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		f[u][0] += std::max(f[v][0], f[v][1] + (DP){0, 1});
		f[u][1] += f[v][0] + (DP){0, 1};
	}
}
void getpath(int u, int t, int fa) {
	if(t == 0) w[u] = 1; else w[u] = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		if(t == 0) getpath(v, f[v][0] < f[v][1] ? 1 : 0, u), w[v] += f[v][0] < f[v][1] ? 1 : 0;
		else getpath(v, 0, u), w[u]++;
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0), getpath(1, f[1][0] < f[1][1] ? 1 : 0, 0);
	auto p = std::max(f[1][0], f[1][1]);
	printf("%d %d\n", p.ans + (n == 2), p.sum);
	for(int i = 1; i <= n; i++) printf("%d ", w[i]);
	return 0;
}