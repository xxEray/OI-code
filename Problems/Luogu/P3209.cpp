#include <bits/stdc++.h>

const int N = 200 + 5;

int n, m;
std::pair<int, int> e[N * 3];
int p[N];

int mod(int x) { return x < 0 ? x + n : x; }

std::vector<int> to[3 * N];
bool ans;
int f[3 * N];
void dfs(int u) {
	for(int v : to[u]) {
		if(f[v] != -1) {
			if(f[v] != !f[u]) ans = false;
		} else f[v] = !f[u], dfs(v);
	}
}

bool vis[3 * N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		if(m > 3 * n) {
			for(int i = 1; i <= m; i++) scanf("%*d%*d");
			for(int i = 1; i <= n; i++) scanf("%*d");
			puts("NO");
			continue;
		}
		for(int i = 1; i <= m; i++) scanf("%d%d", &e[i].first, &e[i].second);
		for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); p[x] = i; }
		for(int i = 1; i <= m; i++) to[i].clear(), f[i] = -1;
		for(int i = 1; i <= m; i++) e[i].first = p[e[i].first], e[i].second = p[e[i].second];
		for(int i = 1; i <= m; i++) vis[i] = (std::abs(e[i].first - e[i].second) == 1 || (e[i].first == n && e[i].second == 1) || (e[i].first == 1 && e[i].second == n));
		for(int i = 1; i <= m; i++) if(!vis[i]) for(int j = 1; j <= m; j++) if(!vis[j]) {
			int i1 = e[i].first, i2 = e[i].second;
			int j1 = e[j].first, j2 = e[j].second;
			int val1 = (mod(j1 - i1) + mod(i2 - j1) == mod(i2 - i1));
			int val2 = (mod(j2 - i1) + mod(i2 - j2) == mod(i2 - i1));
			if(val1 != val2 && i1 != j1 && i1 != j2 && i2 != j1 && i2 != j2) to[i].push_back(j), to[j].push_back(i); // , printf("%d <-> %d\n", i, j);
		}
		ans = true;
		for(int i = 1; i <= m; i++) if(f[i] == -1) f[i] = 0, dfs(i);
		puts(ans ? "YES" : "NO");
	}
	return 0;
}