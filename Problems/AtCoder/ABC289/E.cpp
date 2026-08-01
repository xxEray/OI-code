#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

const int N = 2000 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int a[N];

std::vector<int> e[N], to[N * N];

int hsh(int x, int y) { return (x - 1) * n + y; }
int dis[N * N];
void bfs(int st) {
	std::queue<int> q;
	for(int i = 1; i <= n * n; i++) dis[i] = INF;
	dis[st] = 0, q.push(st);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : to[u]) if(dis[v] == INF) {
			dis[v] = dis[u] + 1;
			q.push(v);
		}
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), e[i].clear();
		for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); e[u].push_back(v), e[v].push_back(u); }
		for(int i = 1; i <= n * n; i++) to[i].clear();
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(a[i] != a[j])
			for(int ni : e[i]) for(int nj : e[j]) if(a[ni] != a[nj])
				to[hsh(i, j)].push_back(hsh(ni, nj));
		bfs(hsh(1, n));
		printf("%d\n", dis[hsh(n, 1)] == INF ? -1 : dis[hsh(n, 1)]);
	}
	return 0;
}