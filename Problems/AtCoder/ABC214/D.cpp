#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 1e5 + 5;

struct Edge { int u, v; LL w; } edge[N];
bool operator<(const Edge &lhs, const Edge &rhs) { return lhs.w < rhs.w; }
int n, m, cedge;

int fa[N]; LL size[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y, size[y] += size[x], size[x] = 0 : 0; }

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); edge[++cedge] = {std::min(u, v), std::max(u, v), w}; }
	std::sort(edge + 1, edge + n);
	for(int i = 1; i <= n; i++) fa[i] = i, size[i] = 1;
	LL ans = 0;
	for(int i = 1; i < n; i++) {
		int u = edge[i].u, v = edge[i].v; LL w = edge[i].w;
		LL szu = size[find(u)], szv = size[find(v)];
		ans += szu * szv * w;
		merge(u, v);
	}
	printf("%lld\n", ans);
	return 0;
} /*
a * b * w + (a + b) * c * w = abw + acw + bcw
b * c * w + (b + c) * a * w = bcw + abw + acw
*/