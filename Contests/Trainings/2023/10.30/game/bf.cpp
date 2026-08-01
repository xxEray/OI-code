#include <bits/stdc++.h>

typedef long long LL;

const int N = 1050 + 5;
const int INF = 0x3f3f3f3f;

int n;

int hash(int x, int y) { return (x - 1) * 1051 + y + 1; }

int dis[N * N];
bool vis[N * N];

std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= hash(1050, 1050); i++) dis[i] = INF;
	dis[hash(1, 0)] = 0;
	q.push({dis[hash(1, 0)], hash(1, 0)});
	while(!q.empty()) {
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		int x = u / 1051 + 1, y = u % 1051 - 1;
		// printf("(%d, %d)\n", x, y);
		auto solve = [&](int v, int w) -> void {
			if(dis[v] <= w) return;
			dis[v] = w;
			q.push({dis[v], v});
		};
		solve(hash(x, x), dis[u] + 1);
		if(x + y <= 1050) solve(hash(x + y, y), dis[u] + 1);
		if(x - 1 >= 1) solve(hash(x - 1, y), dis[u] + 1);
	}
	int ans = INF;
	for(int i = 0; i <= 1050; i++) ans = std::min(ans, dis[hash(n, i)]);
	printf("%d\n", ans);
	return 0;
}