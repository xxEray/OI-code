#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 1e5 + 5;
const int M = 2e5 + 5;

int n, m;

int ind[N], oud[N];
std::vector<int> to[N], ans;

int cur[N];
bool vis[N];
void dfs(int u) {
	// if(vis[u]) { ans.push_back(u); return; }
	// vis[u] = true;
	for(int i = cur[u]; i < (int)to[u].size(); i = cur[u]) cur[u]++, dfs(to[u][i]);
	ans.push_back(u);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[u].push_back(v), ind[v]++, oud[u]++; }
	for(int i = 1; i <= n; i++) std::sort(to[i].begin(), to[i].end(), [&](int x, int y) { return x < y; });
	int id = 0, cnt = 0;
	for(int i = 1; i <= n; i++)
		if(oud[i] == ind[i] + 1) {
			if(id) { puts("No"); return 0; }
			id = i;
		} else if(oud[i] == ind[i] - 1) cnt++;
		else if(oud[i] != ind[i]) { puts("No"); return 0; }
	if(cnt > 1 || (id == 0 && cnt == 1) || (id && cnt == 0)) { puts("No"); return 0; }
	dfs(!id ? 1 : id);
	std::reverse(ans.begin(), ans.end());
	for(int x : ans) printf("%d ", x);
	return 0;
}