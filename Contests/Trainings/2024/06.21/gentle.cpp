#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, m;
std::vector<int> to[N];

int cl[N];
void dfs(int u) { for(int v : to[u]) if(cl[v] == -1) cl[v] = cl[u] ^ 1, dfs(v); }

int du, dv;
int match[N];
bool vis[N];
bool try_match(int u) {
	if(u == du || u == dv || vis[u]) return false;
	vis[u] = true;
	for(int v : to[u]) if(v != du && v != dv && (!match[v] || try_match(match[v]))) {
		match[u] = v, match[v] = u;
		vis[u] = false;
		return true;
	}
	vis[u] = false;
	return false;
}

int main() {
#ifndef DEBUG
	freopen("gentle.in", "r", stdin);
	freopen("gentle.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[u].emplace_back(v), to[v].emplace_back(u); }
	for(int i = 1; i <= n; i++) cl[i] = -1;
	for(int i = 1; i <= n; i++) if(cl[i] == -1) cl[i] = 0, dfs(i);
	// for(int i = 1; i <= n; i++) printf("cl[%d] = %d\n", i, cl[i]);
	int ans = 0, valmax = 0;
	for(int i = 1; i <= n; i++) if(!cl[i]) valmax += try_match(i);
	// printf("valmax = %d\n", valmax);
	for(int u = 1; u <= n; u++) for(int v = u + 1; v <= n; v++) {
		int val = 0;
		du = u, dv = v;
		for(int i = 1; i <= n; i++) match[i] = 0;
		for(int i = 1; i <= n; i++) if(i != du && i != dv && !cl[i]) val += try_match(i);
		// printf("u = %d, v = %d, val = %d\n", u, v, val);
		ans += (valmax == val);
	}
	printf("%d\n", ans);
	return 0;
}