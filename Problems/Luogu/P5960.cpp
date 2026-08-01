#include <bits/stdc++.h>

const int N = 5e3 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
std::vector<std::pair<int, int>> to[N];
int d[N];

int inq[N], inqcnt[N], dis[N];
bool spfa() {
	std::queue<int> q;
	for(int i = 0; i <= n; i++) dis[i] = INF;
	dis[0] = 0, q.push(0);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(auto [v, w] : to[u]) if(dis[v] > dis[u] + w) {
			dis[v] = dis[u] + w;
			if(!inq[v]) {
				inqcnt[v]++, inq[v] = true, q.push(v);
				if(inqcnt[v] > n) return false;
			}
		}
	}
	return true;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int x, y, v;
		scanf("%d%d%d", &x, &y, &v);
		to[y].emplace_back(x, v), d[x]++;
	}
	for(int i = 1; i <= n; i++) if(!d[i]) to[0].emplace_back(i, 0);
	if(!spfa()) puts("NO");
	else for(int i = 1; i <= n; i++) printf("%d ", dis[i]);
	return 0;
}