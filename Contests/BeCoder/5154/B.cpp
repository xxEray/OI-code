#include <bits/stdc++.h>

const int N = 2500 + 5;

int n;
int d[N];
std::vector<int> unvis[N];
std::vector<int> to[N];
std::map<int, int> eid[N];

void solve(int u) {
	while(true) {
		// printf("solve %d\n", u);
		if(unvis[u].empty()) break;
		int id = unvis[u].back();
		unvis[u].pop_back();
		printf("> %d\n", id);
		fflush(stdout);
		int v, degree;
		scanf("%d%d", &v, &degree);
		// printf("Found edge %d -> %d (%d)\n", u, v, id);
		to[u][id] = v, eid[u][v] = id;
		u = v;
		if(!d[u]) {
			// printf("Found new vertice %d!\n", u);
			d[u] = degree;
			for(int i = 1; i <= degree; i++) unvis[u].emplace_back(i);
			to[u].resize(degree + 1);
			n = std::max(n, u);
		}
	}
}

bool vis[N];
void dfs(int u) {
	vis[u] = true;
	// printf("dfs %d\n", u);
	solve(u);
	for(int i = 1; i <= d[u]; i++) {
		int v = to[u][i];
		if(vis[v]) continue;
		printf("> %d\n", i);
		fflush(stdout);
		// printf("Existing edge %d -> %d (%d)\n", u, v, eid[u][v]);
		scanf("%*d%*d");
		dfs(v);
		printf("> %d\n", eid[v][u]);
		// printf("Existing edge %d -> %d (%d)\n", v, u, eid[v][u]);
		fflush(stdout);
		scanf("%*d%*d");
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		n = 0;
		int rt, degree;
		scanf("%d%d", &rt, &degree);
		// printf("Found new vertice %d!\n", rt);
		d[rt] = degree;
		for(int i = 1; i <= degree; i++) unvis[rt].emplace_back(i);
		to[rt].resize(degree + 1);
		n = std::max(n, rt);
		dfs(rt);
		printf("! ");
		for(int u = 1; u <= n; u++) for(int i = 1; i <= d[u]; i++) if(u < to[u][i]) printf("%d %d ", u, to[u][i]);
		puts("");
		fflush(stdout);
		char result[100];
		scanf("%s", result);
		if(strcmp(result, "Correct")) return 0;
		for(int i = 1; i <= n; i++) d[i] = 0, to[i].clear(), unvis[i].clear(), eid[i].clear(), vis[i] = false;
	}
	return 0;
}