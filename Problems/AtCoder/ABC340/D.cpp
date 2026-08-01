#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
std::vector<std::pair<int, LL>> to[N];

LL dis[N];
bool vis[N];
void dijkstra() {
	for(int i = 1; i <= n; i++) dis[i] = LLINF;
	std::priority_queue<std::pair<LL, int>, std::vector<std::pair<LL, int>>, std::greater<std::pair<LL, int>>> q;
	dis[1] = 0;
	q.emplace(dis[1], 1);
	while(!q.empty()) {
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(auto [v, w] : to[u]) if(dis[v] > dis[u] + w) {
			dis[v] = dis[u] + w;
			q.emplace(dis[v], v);
		}
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n - 1; i++) {
		LL a, b; int x;
		scanf("%lld%lld%d", &a, &b, &x);
		to[i].emplace_back(i + 1, a);
		to[i].emplace_back(x, b);
	}
	dijkstra();
	printf("%lld\n", dis[n]);
	return 0;
}