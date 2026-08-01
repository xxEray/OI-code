#include <bits/stdc++.h>

const int N = 100 + 5;

int n, m;
int a[N];

struct Edge { int to, nxt, id; } edge[N * N];
int head[N];
void add_edge(int u, int v, int id) { static int k = 1; edge[k] = (Edge){v, head[u], id}, head[u] = k++; }

bool out[N * N];

int dep[N];
bool vis[N];
void dfs(int u, int fa) {
	vis[u] = true;
	dep[u] = dep[fa] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		if(a[v] == a[u]) {
			if(!vis[v]) out[std::abs(edge[i].id)] = (edge[i].id < 0), dfs(v, u);
			else if(dep[v] < dep[u]) out[std::abs(edge[i].id)] = (edge[i].id < 0);
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v, i), add_edge(v, u, -i); }
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i, 0);
	for(int u = 1; u <= n; u++) for(int i = head[u]; i; i = edge[i].nxt) if(a[edge[i].to] < a[u]) out[std::abs(edge[i].id)] = (edge[i].id < 0);
	for(int i = 1; i <= m; i++) puts(out[i] ? "<-" : "->");
	return 0;
}