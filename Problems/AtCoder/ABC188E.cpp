#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) {
	static int k = 1;
	edge[k] = (Edge){v, head[u]};
	head[u] = k++;
}

LL a[N];
int n, m;

LL f[N];

int main() {
	std::scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) std::scanf("%lld", &a[i]);
	for(int i = 1; i <= m; i++) {
		int u, v;
		std::scanf("%d%d", &u, &v);
		add_edge(v, u);
	}
	for(int i = 1; i <= n; i++) f[i] = LLINF;
	for(int i = 1; i <= n; i++)
		for(int j = head[i]; j; j = edge[j].nxt)
			f[i] = std::min(f[i], std::min(f[edge[j].to], a[edge[j].to]));
	LL ans = -LLINF;
	for(int i = 1; i <= n; i++) ans = std::max(ans, a[i] - f[i]);
	std::printf("%lld\n", ans);
	return 0;
}