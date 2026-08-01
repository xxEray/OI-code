#include <bits/stdc++.h>

const int N = 3e5 + 5;

int n;
int a[N], b[N], last[N];
struct Edge { int to, nxt, w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

std::priority_queue<std::pair<int, int>> q, q2;
// int vis[N];
bool updated[N];

int ind[N];

int main() {
#ifndef DEBUG
	freopen("infect.in", "r", stdin);
	freopen("infect.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = a[i];
	for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
	for(int i = 1; i <= n; i++) q2.emplace(a[i], i);
	int ans = 0;
	while(!q2.empty()) {
		int uu = q2.top().second;
		q2.pop();
		if(updated[uu]) continue;
		printf("uu = %d\n", uu);
		// vis[uu] = true;
		ans++;
		q.emplace(a[uu], uu);
		while(!q.empty()) {
			auto [wu, u] = q.top();
			q.pop();
			if(wu < a[u]) continue;
			// printf("u = %d\n", u);
			updated[u] = true;
			for(int i = head[u]; i; i = edge[i].nxt) {
				int v = edge[i].to, w = edge[i].w;
				if(a[u] < w) continue;
				if(a[v] < a[u] - w) a[v] = a[u] - w, q.emplace(a[v], v), q2.emplace(a[v], v);
				else if(!updated[v]) q.emplace(a[v], v);
				// printf("%d -> %d\n", u, v);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
} /*
10
1 2 2 2 6 3 4 5 4 3
1 2 5
2 3 1
2 4 5
4 5 2
4 6 4
4 7 3
1 8 1
8 9 5
8 10 4
*/