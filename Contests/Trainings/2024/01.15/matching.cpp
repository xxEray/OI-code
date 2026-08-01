#include <bits/stdc++.h>

const int N = 500 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int id[2 * N][2 * N], color[2 * N][2 * N];
bool chosen[2 * N][2 * N];
std::vector<int> to[2 * N];
int match[2 * N];
bool instk[N];

bool dfs(int u) {
	instk[u] = true;
	for(int v : to[u]) if(!match[v] || (!instk[match[v]] && dfs(match[v]))) return match[u] = v, match[v] = u, true;
	return false;
}

std::vector<int> to2[4 * N];
int dis[4 * N], last[4 * N];

int main() {
#ifndef DEBUG
	freopen("matching.in", "r", stdin);
	freopen("matching.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= 2 * n; i++) match[i] = 0, to[i].clear();
		for(int i = 1; i <= 4 * n; i++) to2[i].clear();
		for(int i = 1; i <= 2 * n; i++) for(int j = 1; j <= 2 * n; j++) id[i][j] = color[i][j] = chosen[i][j] = 0;
		for(int i = 1; i <= n; i++) instk[i] = 0;
		for(int i = 1; i <= m; i++) {
			int u, v, c;
			scanf("%d%d%d", &u, &v, &c);
			to[u].emplace_back(v), to[v].emplace_back(u);
			id[u][v] = id[v][u] = i;
			color[u][v] = color[v][u] = c;
		}
		int flow = 0;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) instk[j] = false;
			flow += dfs(i);
		}
		if(flow < n) { puts("-1"); continue; }
		int cnt1 = 0;
		for(int u = 1; u <= n; u++) for(int v : to[u]) if(match[u] == v) chosen[u][v] = true, cnt1 += color[u][v];
		// for(int u = 1; u <= n; u++) printf("%d <-> %d\n", u, match[u]);
		bool flag = false;
		if(cnt1 & 1) {
			for(int u = 1; u <= n; u++) for(int v : to[u]) if(match[u] != v) to2[u].emplace_back(v + color[u][v] * 2 * n), to2[u + 2 * n].emplace_back(v + !color[u][v] * 2 * n);
			for(int i = n + 1; i <= 2 * n; i++) to2[i].emplace_back(match[i] + color[i][match[i]] * 2 * n), to2[i + 2 * n].emplace_back(match[i] + !color[i][match[i]] * 2 * n);
			auto bfs = [&](int st) {
				std::queue<int> q;
				for(int i = 1; i <= 4 * n; i++) dis[i] = INF, last[i] = 0;
				q.push(st), dis[st] = 0;
				while(!q.empty()) {
					int u = q.front();
					q.pop();
					for(int v : to2[u]) if(dis[v] == INF) dis[v] = dis[u] + 1, last[v] = u, q.push(v);
				}
				return dis[st + 2 * n];
			};
			int opt = 0, optval = INF;
			for(int i = 1; i <= n; i++) {
				auto val = bfs(i);
				if(val < optval) optval = val, opt = i;
			}
			bfs(opt);
			if(optval < INF) {
				flag = true;
				// printf("opt: %d\n", opt);
				// for(int i = 1; i <= 4 * n; i++) printf("%d ", last[i]);
				int u = opt + 2 * n;
				do {
					auto trim = [&](int x) { return x > 2 * n ? x - 2 * n : x; };
					chosen[trim(last[u])][trim(u)] ^= 1, chosen[trim(u)][trim(last[u])] ^= 1;
					u = last[u];
				} while(u != opt);
			}
		} else flag = true;
		if(flag) {
			for(int u = 1; u <= n; u++) for(int v : to[u]) if(u < v && chosen[u][v]) printf("%d ", id[u][v]);
			puts("");
		} else puts("-1");
	}
	return 0;
} /*
1
3 7
3 6 1
2 6 0
2 5 1
3 5 1
1 6 1
3 4 0
1 5 1
*/