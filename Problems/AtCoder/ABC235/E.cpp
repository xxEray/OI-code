#include <cstdio>
#include <algorithm>
#include <assert.h>

const int N = 4e5 + 5;

struct Edge { int x, y, w, type, ans, id; } edge[N];
int n, m, Q;
int cnt;

bool operator<(Edge x, Edge y) { return x.w < y.w; }

int fa[N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int out[N];

int main() {
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 1; i <= m; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); edge[++cnt] = {u, v, w, 1, -1, -1}; }
	for(int i = 1; i <= Q; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); edge[++cnt] = {u, v, w, 0, -1, i}; }
	std::sort(edge + 1, edge + cnt + 1);
	for(int i = 1; i <= cnt; i++) {
		int u = edge[i].x, v = edge[i].y, t = edge[i].type;
		if(find(u) != find(v)) {
			if(t == 1) merge(u, v);
			else edge[i].ans = 1;
		} else {
			if(t == 0) edge[i].ans = 0;
		}
	}
	for(int i = 1; i <= cnt; i++) if(edge[i].type == 0) out[edge[i].id] = edge[i].ans;
	for(int i = 1; i <= Q; i++) {
		assert(out[i] != -1);
		puts(out[i] == 0 ? "No" : "Yes");
	}
	return 0;
}