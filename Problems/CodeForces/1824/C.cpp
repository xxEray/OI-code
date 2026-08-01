#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n;
int a[N];
int head[N];
struct Edge { int to, nxt; } edge[N << 1];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int f[N];
std::set<int> st[N];
void dfs(int u, int fa) {
	int cnt = 0;
	std::map<int, int> mp;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		cnt++;
		a[v] ^= a[u];
		dfs(v, u);
		f[u] += f[v];
		if(st[u].size() < st[v].size()) std::swap(st[u], st[v]);
		for(int x : st[v]) {
			if(st[u].count(x)) mp[x]++;
			st[u].insert(x);
		}
	}
	if(!mp.empty()) {
		int mx = 0;
		for(auto &p : mp) mx = std::max(mx, p.second);
		f[u] += cnt - (mx + 1);
		st[u].clear();
		for(auto &p : mp) if(p.second == mx) st[u].insert(p.first);
	} else {
		if(st[u].empty()) st[u].insert(a[u]), f[u] = 0;
		else f[u] += cnt - 1;
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0);
	printf("%d\n", f[1] + (st[1].count(0) ? 0 : 1));
	return 0;
}