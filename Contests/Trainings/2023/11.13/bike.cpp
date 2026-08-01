#include <bits/stdc++.h>

const int N = 500 + 5;
const int INF = 0x3f3f3f3f;

int n, W;
int a[N][N], b[N][N];
int na[N][N], nb[N][N];

int fa[N];
void init() { for(int i = 1; i <= n; i++) fa[i] = i; }
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

struct Edge { int u, v, w; };
std::vector<Edge> edge1, edge2, ans;

int main() {
#ifndef DEBUG
	freopen("bike.in", "r", stdin);
	freopen("bike.out", "w", stdout);
#endif
	scanf("%d%d", &n, &W);
	for(int i = 1; i <= n; i++) a[i][i] = b[i][i] = -INF;
	for(int i = 1; i <= n; i++) for(int j = 1; j < i; j++) scanf("%d", &a[i][j]), a[j][i] = a[i][j];
	for(int i = 1; i <= n; i++) for(int j = 1; j < i; j++) scanf("%d", &b[i][j]), b[j][i] = b[i][j];
	for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) if(a[i][j] + b[i][j] >= W) edge1.push_back({i, j, a[i][j]}), edge2.push_back({i, j, b[i][j]});
	std::sort(edge1.begin(), edge1.end(), [&](const Edge &x, const Edge &y) { return x.w > y.w; });
	std::sort(edge2.begin(), edge2.end(), [&](const Edge &x, const Edge &y) { return x.w > y.w; });
	init();
	for(auto [u, v, w] : edge1) if(find(u) != find(v)) merge(u, v), ans.push_back({u, v, w});
	for(int i = 1; i <= n; i++) if(find(i) != find(1)) { puts("NO"); return 0; }
	init();
	for(auto [u, v, w] : edge2) if(find(u) != find(v)) merge(u, v), ans.push_back({u, v, W - w});
	for(int i = 1; i <= n; i++) if(find(i) != find(1)) { puts("NO"); return 0; }
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) na[i][j] = nb[i][j] = -INF;
	for(auto [u, v, w] : ans) na[u][v] = na[v][u] = std::max(na[u][v], w), nb[u][v] = nb[v][u] = std::max(nb[u][v], W - w);
	for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) na[i][j] = std::max(na[i][j], std::min(na[i][k], na[k][j]));
	for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) nb[i][j] = std::max(nb[i][j], std::min(nb[i][k], nb[k][j]));
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) printf("[%d][%d]: a=%d, b=%d, na=%d, nb=%d\n", i, j, a[i][j], b[i][j], na[i][j], nb[i][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(i != j && (na[i][j] != a[i][j] || nb[i][j] != b[i][j])) { puts("NO"); return 0; }
	printf("%d\n", (int)ans.size());
	for(auto [u, v, w] : ans) printf("%d %d %d\n", u - 1, v - 1, W - w);
	return 0;
} /*
2 1
1
1
*/