#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, m, T;
int a[N];
std::vector<std::pair<int, int>> edges[N];
std::vector<std::pair<int, int>> to[N];

std::vector<int> appear[N];

int dis[N];
std::set<int> st[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int cnt; scanf("%d", &cnt);
		while(cnt--) {
			int u, v;
			scanf("%d%d", &u, &v);
			edges[i].push_back({u, v});
		}
	}
	scanf("%d", &T);
	for(int i = 1; i <= T; i++) scanf("%d", &a[i]);
	for(int i = T; i >= 1; i--) {
		if(appear[a[i]].empty()) {
			for(const auto &[u, v] : edges[a[i]]) to[u].push_back({v, a[i]}), to[v].push_back({u, a[i]});
		}
		appear[a[i]].push_back(i);
	}
	for(int i = 1; i <= n; i++) dis[i] = T + 1;
	dis[1] = 1, st[0].insert(1);
	for(int i = 1; i <= T; i++) {
		for(int u : st[i - 1])
			for(const auto &[v, t] : to[u]) if(appear[t].back() < dis[v]) {
				if(dis[v] <= T) st[dis[v]].erase(v);
				dis[v] = appear[t].back();
				st[dis[v]].insert(v);
			}
		appear[a[i]].pop_back();
		if(appear[a[i]].empty()) {
			for(const auto &[u, v] : edges[a[i]]) to[u].pop_back(), to[v].pop_back();
		}
	}
	printf("%d\n", dis[n] == T + 1 ? -1 : dis[n]);
	return 0;
}