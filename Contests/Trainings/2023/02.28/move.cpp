#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int n;
struct Edge { int to, nxt; } edge[N << 1];
int head[N], ek;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }

namespace Solve1 {
	int p[N];
	int dfn[N], sz[N], fa[N], ts;
	void dfs(int u) {
		dfn[u] = ++ts;
		sz[u] = 1;
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
			int v = edge[i].to;
			fa[v] = u;
			dfs(v);
			sz[u] += sz[v];
		}
	}
	bool ancestor(int u, int v) { return dfn[u] <= dfn[v] && dfn[v] <= dfn[u] + sz[u] - 1; }
	bool exist[N];
	bool out[N];
	void main() {
		ts = 0;
		for(int i = 1; i <= n; i++) fa[i] = dfn[i] = sz[i] = out[i] = exist[i] = 0;
		dfs(1);
		for(int i = 1; i <= n; i++) out[i] = false;
		for(int i = 1; i <= n; i++) p[i] = i;
		do {
			int now = 1;
			for(int i = 1; i <= n; i++) exist[i] = false;
			exist[0] = true;
			bool flag = true;
			for(int i = 1; i <= n; i++) flag &= exist[fa[p[i]]], exist[p[i]] = true;
			if(!flag) continue;
			for(int i = 2; i <= n; i++)
				if(ancestor(now, p[i])) {
					for(int j = head[now]; j; j = edge[j].nxt) if(edge[j].to != fa[now] && ancestor(edge[j].to, p[i])) { now = edge[j].to; break; }
				} else now = fa[now];
			out[now] = true;
		} while(std::next_permutation(p + 1, p + n + 1));
		for(int i = 1; i <= n; i++) printf("%d", out[i]);
		puts("");
	}
}

namespace Solve3 {
	int sz[N];
	void dfs(int u, int fa) {
		sz[u] = 1;
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
			int v = edge[i].to;
			dfs(v, u);
			sz[u] += sz[v];
		}
	}
	void main() {
		dfs(1, 0);
		int sum = 0, mx = 0;
		for(int i = head[1]; i; i = edge[i].nxt) sum += sz[edge[i].to], mx = std::max(mx, sz[edge[i].to]);
		if(sum - mx >= mx && (sum & 1) == 0) printf("1");
		else printf("0");
	}
}

int main() {
#ifndef DEBUG
	freopen("move.in", "r", stdin);
	freopen("move.out", "w", stdout);
#endif
	int W, T; scanf("%d%d", &W, &T);
	while(T--) {
		ek = 1;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) head[i] = 0;
		for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
		if(W == 1 || W == 0) Solve1::main();
		else if(W == 3) Solve3::main();
	}
	return 0;
} /*
3 3
4
1 2
1 3
1 4
6
1 2
1 3
1 4
4 5
5 6
10
1 2
1 3
3 4
3 5
3 6
4 7
7 8
8 9
9 10
*/
