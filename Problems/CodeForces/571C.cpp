#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, m;
std::vector<int> a[N];
int appear[N], occur[N][3];
int ans[N];

bool ok[N];

std::set<int> to[3][N];
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

bool vis[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		int k, x;
		scanf("%d", &k);
		while(k--) scanf("%d", &x), a[i].push_back(x), appear[std::abs(x)] |= (x > 0 ? 1 : 2), occur[std::abs(x)][x > 0 ? 1 : 2] = i;
	}
	for(int i = 1; i <= n; i++) for(int x : a[i]) if(appear[std::abs(x)] != 3) ok[i] = true;
	for(int i = 1; i <= m; i++) if(appear[i] != 3) ans[i] = (appear[i] == 1 ? 2 : 1);
	std::queue<int> q;
	for(int i = 1; i <= n; i++) if(ok[i]) q.push(i);
	while(!q.empty()) {
		int u = q.front();
		// printf("u = %d\n", u);
		q.pop();
		for(int x : a[u]) if(appear[std::abs(x)] == 3 && !ans[std::abs(x)]) {
			int v = occur[std::abs(x)][x > 0 ? 2 : 1];
			ans[std::abs(x)] = (x > 0 ? 1 : 2);
			ok[v] = true;
			q.push(v);
			// printf("%d -> %d\n", u, v);
		}
	}
	// printf("ok: "); for(int i = 1; i <= n; i++) printf("%d ", ok[i]); puts("");
	for(int i = 1; i <= m; i++) if(appear[i] == 3 && !ok[occur[i][1]]) assert(!ok[occur[i][2]]), to[1][occur[i][1]].insert(i), to[2][occur[i][2]].insert(i);
	for(int i = 1; i <= n; i++) if(!ok[i]) pq.push({to[1][i].size() + to[2][i].size(), i});
	while(!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		if(vis[u]) continue;
		vis[u] = true;
		int t = (to[1][u].empty() ? 2 : 1);
		if(to[t][u].empty()) { puts("NO"); return 0; }
		int p = *to[t][u].begin();
		to[t][u].erase(to[t][u].begin());
		ans[p] = (t == 1 ? 2 : 1);
		int v = occur[p][3 - t];
		to[3 - t][v].erase(p);
		pq.push({to[1][v].size() + to[2][v].size(), v});
		// printf("u = %d, p = %d, v = %d\n", u, p, v);
	}
	puts("YES");
	for(int i = 1; i <= m; i++) printf("%d", std::max(ans[i] - 1, 0));
	puts("");
	return 0;
} /*
5 5
3 2 3 -5
1 4
2 -1 -4
2 1 -2
2 -3 5
*/