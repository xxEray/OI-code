#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

struct Edge { int to, nxt, id; } edge[N << 1];
int head[N], ek;
void add_edge(int u, int v, int id) { edge[ek] = (Edge){v, head[u], id}, head[u] = ek++; }
int n;

int out[N], d[N];

void dfs(int u, int fa, int w) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		w = 5 - w;
		out[edge[i].id] = w;
		dfs(v, u, w);
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		ek = 1;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) d[i] = 0, head[i] = 0;
		for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v, i), add_edge(v, u, i); d[u]++, d[v]++; }
		bool fl = true;
		for(int i = 1; i <= n; i++) if(d[i] != 1 && d[i] != 2) fl = false;
		if(!fl) { puts("-1"); continue; }
		dfs(1, 0, 2);
		for(int i = 1; i < n; i++) printf("%d ", out[i]);
		puts("");
	}
	return 0;
} /*
3
2
1 2
4
1 3
4 3
2 1
7
1 2
1 3
3 4
3 5
6 2
7 2

*/