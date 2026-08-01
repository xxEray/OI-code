#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

const int N = 1e3 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int a[N];

struct Edge { int to, nxt, r; } edge[N * N * 2 + N * 4];
int head[N], cur[N];
void add_edge(int u, int v, int c) { static int k = 2; edge[k] = (Edge){v, head[u], c}, head[u] = k++; }
struct Dinic {
	int dep[N];
	int src, dst;
	bool bfs() {
		std::queue<int> q;
		for(int i = 1; i <= n + 2; i++) dep[i] = 0;
		dep[src] = 1, q.push(src);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int i = head[u]; i; i = edge[i].nxt) {
				int v = edge[i].to;
				if(dep[v] || !edge[i].r) continue;
				dep[v] = dep[u] + 1;
				q.push(v);
			}
		}
		return dep[dst];
	}
	int dfs(int u, int in) {
		// printf("dfs %d %d\n", u, in);
		if(u == dst) return in;
		int out = 0;
		for(int &i = cur[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(dep[v] != dep[u] + 1 || !edge[i].r) continue;
			int ret = dfs(v, std::min(in, edge[i].r));
			out += ret, in -= ret;
			edge[i].r -= ret, edge[i ^ 1].r += ret;
			if(!in) break;
		}
		if(!out) dep[u] = 0;
		return out;
	}
	int maxflow(int src_, int dst_) {
		src = src_, dst = dst_;
		int ans = 0;
		while(bfs()) {
			for(int i = 1; i <= n + 2; i++) cur[i] = head[i];
			ans += dfs(src, INF);
		}
		return ans;
	}
} dinic;

bool vis[N];
std::vector<std::pair<int, int>> ans;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1);
	if(a[n] * 2 + 1 > m) { puts("-1"); return 0; }
	int K = 0;
	while(K < n && a[K + 1] * 3 <= m) K++;
	int src = n + 1, dst = n + 2;
	for(int i = 1; i <= K; i++) add_edge(src, i, 1), add_edge(i, src, 0);
	for(int i = K + 1; i <= n; i++) add_edge(i, dst, 1), add_edge(dst, i, 0);
	for(int i = 1; i <= K; i++)
		for(int j = K + 1; j <= n; j++)
			if(a[j] % a[i] == 0 && 2 * a[j] + a[i] <= m)
				add_edge(i, j, 1), add_edge(j, i, 0);
	int flow = dinic.maxflow(src, dst);
	// printf("flow = %d\n", flow);
	if(flow < n - K) { puts("-1"); return 0; }
	for(int u = K + 1; u <= n; u++)
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(v == dst) continue;
			if(edge[i].r) {
				vis[u] = vis[v] = true;
				// printf("%d - %d\n", u, v);
				ans.push_back({2 * a[u] + a[v], a[u] + a[v]});
				break;
			}
		}
	for(int i = 1; i <= K; i++) if(!vis[i]) ans.push_back({3 * a[i], 2 * a[i]});
	printf("%d\n", (int)ans.size());
	for(auto p : ans) printf("%d %d\n", p.first, p.second);
	return 0;
}