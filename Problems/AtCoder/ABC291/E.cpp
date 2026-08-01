#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 5;

int n, m;
std::vector<int> to[N];

int ind[N], f[N], out[N];

void dfs(int u) {
	if(f[u]) return;
	f[u] = 1;
	for(int v : to[u]) dfs(v), f[u] = std::max(f[u], f[v] + 1);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[u].push_back(v), ind[v]++; }
	int cnt = 0;
	for(int i = 1; i <= n; i++) cnt += !ind[i];
	if(cnt > 1) { puts("No"); return 0; }
	int id = 0;
	for(int i = 1; i <= n; i++) if(!ind[i]) id = i;
	dfs(id);
	if(f[id] < n) puts("No");
	else {
		puts("Yes");
		int u = id, c = 0;
		while(c < n) {
			out[u] = ++c;
			for(int v : to[u]) if(f[v] == f[u] - 1) { u = v; break; }
		}
		for(int i = 1; i <= n; i++) printf("%d ", out[i]);
		puts("");
	}
	return 0;
}