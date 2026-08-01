#include <bits/stdc++.h>

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int n, K;
int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int d[N];
void bfs() {
	std::queue<int> q;
	for(int i = 1; i <= n; i++) d[i] = INF;
	for(int i = 1; i <= n; i++) if(a[i] == 1) d[i] = 0, q.push(i);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(d[v] < INF) continue;
			d[v] = d[u] + 1;
			q.push(v);
		}
	}
}

int ans;
std::pair<int, int> dfs(int u, int fa) {
	int mx = -1, up = -1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		auto p = dfs(v, u);
		up = std::max(up, p.second - 1);
		if(p.first == -1) continue;
		if(d[u] > d[v]) assert(mx == -1 || p.first + 1 == mx), mx = p.first + 1, up = std::max(up, d[v] - 1);
		else ans++, up = std::max(up, d[v] - 1);
	}
	if(a[u] == 1) mx = 0;
	if(mx >= 0 && up == mx) mx = -1;
	// printf("dfs %d: d=%d, return {%d, %d}\n", u, d[u], mx, up);
	return {mx, up};
}

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= K; i++) { int u; scanf("%d", &u); a[u] = 1; }
	bfs();
	auto p = dfs(1, 0);
	printf("%d\n", ans + (p.first >= 0 ? 1 : 0));
	return 0;
} /*
4 2
1 2
2 3
3 4
2 3
*/