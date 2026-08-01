#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

typedef long long LL;

const int N = 5e4 + 5;
const int M = 3e5 + 5;
const int INF = 0x3f3f3f3f;

int n, Q;
LL pivot;

struct Edge { int u, v; LL w; } e[M];

bool vis[N];
LL dis[N];
std::vector<std::pair<int, LL>> to[N];
std::priority_queue<std::pair<int, LL>, std::vector<std::pair<int, LL>>, std::greater<std::pair<int, LL>>> q;
LL dijkstra(int l, int r) {
	r = std::min(r, Q);
	for(int i = l; i <= r; i++) vis[e[i].u] = vis[e[i].v] = 0, dis[e[i].u] = dis[e[i].v] = INF, to[e[i].u].clear(), to[e[i].v].clear();
	vis[1] = vis[n] = 0, dis[1] = dis[n] = INF, to[1].clear(), to[n].clear();
	for(int i = l; i <= r; i++) to[e[i].u].push_back({e[i].v, e[i].w}), to[e[i].v].push_back({e[i].u, e[i].w});
	dis[1] = 0, q.push({0, 1});
	while(!q.empty()) {
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(auto &p : to[u]) {
			int v = p.first;
			LL w = p.second;
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				q.push({dis[v], v});
			}
		}
	}
	return dis[n];
}
std::vector<int> ans;

int main() {
	scanf("%d%d%lld", &n, &Q, &pivot);
	for(int i = 1; i <= Q; i++) scanf("%d%d%lld", &e[i].u, &e[i].v, &e[i].w);
	int now = 1;
	while(now <= Q) {
		int rb = 0;
		while(now + (1 << rb) - 1 <= 2 * Q && dijkstra(now, now + (1 << rb) - 1) > pivot) rb++;
		if(now + (1 << rb) - 1 > 2 * Q) break;
		int l = now, r = std::min(now + (1 << rb) - 1, Q);
		while(l < r) {
			int mid = (l + r) >> 1;
			if(dijkstra(now, mid) <= pivot) r = mid;
			else l = mid + 1;
		}
		ans.push_back(l);
		now = l + 1;
	}
	printf("%d\n", (int)ans.size());
	for(int v : ans) printf("%d ", v);
	puts("");
	return 0;
}
