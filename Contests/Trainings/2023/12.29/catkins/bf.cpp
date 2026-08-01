#include <bits/stdc++.h>

const int N = 5000 + 5;

int n, Q;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int dfn[N], dfl[N], time_stamp;
void predfs(int u, int fa) {
	dfn[u] = ++time_stamp, dfl[dfn[u]] = u;
	std::vector<int> son;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		son.emplace_back(v);
	}
	std::sort(son.begin(), son.end());
	for(int v : son) predfs(v, u);
}

bool tag[N];
void dfs(int u) {
	tag[u] = false;
	for(int i = head[u]; i; i = edge[i].nxt) if(tag[edge[i].to]) dfs(edge[i].to);
}

int main() {
	scanf("%d%d%*d", &n, &Q);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	predfs(1, 0);
	while(Q--) {
		for(int i = 1; i <= n; i++) tag[i] = false;
		int k;
		scanf("%d", &k);
		while(k--) {
			int l, r;
			scanf("%d%d", &l, &r);
			for(int i = l; i <= r; i++) tag[dfl[i]] = true;
		}
		int cnt = 0;
		for(int i = 1; i <= n; i++) if(tag[i]) cnt++, dfs(i);
		printf("%d\n", cnt - 1);
	}
	return 0;
} /*
6 2 0
1 3
1 2
2 4
2 5
3 6
2
1 3 5 6
1
4 5
*/