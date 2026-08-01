#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, m;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 2; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

bool vis[N];
int fa[N];
int dfn[N], time_stamp;
int last, diff, almost;
std::vector<std::array<int, 3>> stk;
void dfs(int u, int fbde) {
	// printf("dfs(%d), last = %d\n", u, last);
	vis[u] = true;
	dfn[u] = ++time_stamp;
	for(int i = head[u]; i; i = edge[i].nxt) if(i != fbde) {
		int v = edge[i].to;
		if(!vis[v]) fa[v] = u, dfs(v, i ^ 1);
		else if(dfn[v] <= dfn[u]) {
			// printf("%d: reach %d!\n", u, v);
			if(last && dfn[v] < dfn[diff]) {
				puts("YES");
				int d0 = diff, d1 = last, up = almost, dn = v;
				if(dfn[d1] < dfn[dn]) {
					std::swap(d1, dn);
					std::vector<int> vct;
					int w = d0; while(w != d1) vct.push_back(w), w = fa[w]; vct.push_back(d1);
					std::reverse(vct.begin(), vct.end());
					printf("%d ", (int)vct.size()); for(int x : vct) printf("%d ", x); puts("");
					vct.clear();
					w = d1; while(w != dn) vct.push_back(w), w = fa[w]; vct.push_back(dn);
					w = up; while(w != d0) vct.push_back(w), w = fa[w]; vct.push_back(d0);
					printf("%d ", (int)vct.size()); for(int x : vct) printf("%d ", x); puts("");
					vct.clear();
					vct.push_back(d1);
					w = u; while(w != d0) vct.push_back(w), w = fa[w]; vct.push_back(d0);
					printf("%d ", (int)vct.size()); for(int x : vct) printf("%d ", x); puts("");
				} else {
					std::vector<int> vct;
					int w = d0; while(w != d1) vct.push_back(w), w = fa[w]; vct.push_back(d1);
					std::reverse(vct.begin(), vct.end());
					printf("%d ", (int)vct.size()); for(int x : vct) printf("%d ", x); puts("");
					vct.clear();
					w = d1; while(w != dn) vct.push_back(w), w = fa[w]; vct.push_back(dn);
					w = u; while(w != d0) vct.push_back(w), w = fa[w]; vct.push_back(d0);
					printf("%d ", (int)vct.size()); for(int x : vct) printf("%d ", x); puts("");
					vct.clear();
					vct.push_back(d1);
					w = up; while(w != d0) vct.push_back(w), w = fa[w]; vct.push_back(d0);
					printf("%d ", (int)vct.size()); for(int x : vct) printf("%d ", x); puts("");
				}
				exit(0);
			} else last = v, almost = u, stk.empty() ? 0 : stk.back()[2] = diff, stk.push_back({last, almost, 0});
		}
		if(last == u) {
			// printf("%d: %d failed!\n", u, last);
			stk.pop_back();
			last = (stk.empty() ? 0 : stk.back()[0]);
			almost = (stk.empty() ? 0 : stk.back()[1]);
			diff = (stk.empty() ? 0 : stk.back()[2]);
		}
		if(last && dfn[u] <= dfn[almost]) diff = u;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i, 0);
	puts("NO");
	return 0;
} /*
8 11
3 1
3 6
6 8
7 8
6 7
5 6
3 5
4 2
3 4
2 3
1 2
*/