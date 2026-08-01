#include <bits/stdc++.h>

const int N = 1e6 + 5;
const int INF = 0x3f3f3f3f;

int n, Q;
int dep[N], fa[N];
std::vector<int> to[N];

int f[N];
std::vector<int> dp[N], copy[N];

void bfs() {
	std::queue<int> q;
	for(int i = 1; i <= n; i++) f[i] = INF;
	for(int i = 1; i <= n; i++) if(to[i].size() == 1) f[i] = 0, q.push(i);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : to[u]) if(f[v] == INF) {
			f[v] = f[u] + 1;
			q.push(v);
		}
	}
}

int ans;
void dfs(int u, int x) {
	for(int v : to[u]) if(v != fa[u]) {
		dfs(v, x);
		if(dp[v].size() > dp[u].size()) dp[u].swap(dp[v]);
		for(int i = 0; i < (int)dp[v].size(); i++)
			while(ans < n) {
				int bd = std::max(ans + 1 - x - i, 0);
				if(bd < (int)dp[u].size() && dp[v][i] + dp[u][bd] - 2 * dep[u] >= ans + 1) ans++;
				else break;
			}
		for(int i = 0; i < (int)dp[v].size(); i++) dp[u][i] = std::max(dp[u][i], dp[v][i]);
	}
	while(ans < n) {
		int bd = std::max(ans + 1 - x - f[u], 0);
		if(bd < (int)dp[u].size() && dp[u][bd] - dep[u] >= ans + 1) ans++;
		else break;
	}
	if((int)dp[u].size() == f[u]) dp[u].push_back(dep[u]);
	// copy[u] = dp[u];
}
int solve(int x) {
	ans = 0;
	for(int i = 1; i <= n; i++) std::vector<int>().swap(dp[i]);
	dfs(1, x);
	// printf("\nQuery %d\n", x);
	// for(int i = 1; i <= n; i++) {
	// 	printf("%d: dep=%d, f=%d, dp=", i, dep[i], f[i]);
	// 	for(int j : copy[i]) printf("%d ", j);
	// 	puts("");
	// }
	return ans;
}

int main() {
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) scanf("%d", &fa[i]), to[fa[i]].push_back(i), to[i].push_back(fa[i]);
	bfs();
	for(int i = 1; i <= n; i++) dep[i] = dep[fa[i]] + 1;
	scanf("%d", &Q);
	while(Q--) {
		int x;
		scanf("%d", &x);
		printf("%d ", solve(x));
	}
	puts("");
	return 0;
}