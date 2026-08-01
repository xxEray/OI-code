#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
std::vector<std::pair<int, int>> to[N];

int dis[N];
void dfs(int u) {
	if(~dis[u]) return;
	dis[u] = 0;
	for(auto [v, _] : to[u]) dfs(v), dis[u] = std::max(dis[u], dis[v] + 1);
}

std::vector<int> vct[N];
LL sum[N];
int order[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); to[u].emplace_back(v, w); }
	for(int i = 1; i <= n; i++) dis[i] = -1;
	for(int i = 1; i <= n; i++) dfs(i);
	for(int u = 1; u <= n; u++) {
		std::vector<std::pair<int, int>> tmp;
		for(auto [v, w] : to[u]) if(dis[v] + 1 == dis[u]) tmp.emplace_back(v, w);
		to[u].swap(tmp);
	}
	for(int i = 1; i <= n; i++) vct[dis[i]].emplace_back(i);
	int c = 0;
	for(int u : vct[0]) order[u] = ++c;
	for(int o = 1; o <= n; o++) {
		std::vector<std::array<int, 3>> tmp;
		for(int u : vct[o]) {
			std::sort(to[u].begin(), to[u].end(), [&](std::pair<int, int> x, std::pair<int, int> y) { return x.second == y.second ? order[x.first] < order[y.first] : x.second < y.second; });
			int last = 0, lastw = INF;
			for(auto [v, w] : to[u]) if(lastw > w || (lastw == w && order[last] > order[v])) lastw = w, last = v;
			sum[u] = sum[last] + lastw;
			tmp.push_back({lastw, order[last], u});
		}
		std::sort(tmp.begin(), tmp.end());
		c = 0;
		for(auto [_, __, u] : tmp) order[u] = ++c;
	}
	for(int i = 1; i <= n; i++) printf("%d %lld\n", dis[i], sum[i]);
	return 0;
}