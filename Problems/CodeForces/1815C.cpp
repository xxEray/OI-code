#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

const int N = 1500 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
std::vector<int> to[N];

int dis[N];
void bfs(int st) {
	std::queue<int> q;
	q.push(st), dis[st] = 1;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : to[u]) if(dis[v] == INF) {
			dis[v] = dis[u] + 1;
			q.push(v);
		}
	}
}

std::vector<int> vct[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) to[i].clear(), dis[i] = INF, vct[i].clear();
		for(int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			to[y].push_back(x);
		}
		bfs(1);
		bool flag = false;
		int mx = 0;
		for(int i = 1; i <= n; i++)
			if(dis[i] == INF) flag = true;
			else vct[dis[i]].push_back(i), mx = std::max(mx, dis[i]);
		// for(int i = 1; i <= n; i++) printf("dis[%d] = %d\n", i, dis[i]);
		if(flag) puts("INFINITE");
		else {
			puts("FINITE");
			std::vector<int> ans;
			for(int i = mx; i >= 2; i--) for(int j = i; j <= mx; j++) for(int x : vct[j]) ans.push_back(x);
			for(int j = 1; j <= mx; j++) for(int x : vct[j]) ans.push_back(x);
			printf("%d\n", (int)ans.size());
			for(int x : ans) printf("%d ", x);
			puts("");
		}
	}
	return 0;
}