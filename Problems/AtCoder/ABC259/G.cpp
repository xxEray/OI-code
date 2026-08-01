#include <cstdio>
#include <algorithm>
#include <atcoder/maxflow>

typedef long long LL;

const int N = 100 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
int a[N][N];

int main() {
	scanf("%d%d", &n, &m);
	atcoder::mf_graph<LL> G(n + m + 2);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
	int src = 0, dst = 1;
	for(int i = 1; i <= n; i++) {
		LL sum = 0;
		for(int j = 1; j <= m; j++) if(a[i][j] < 0) sum += std::abs(a[i][j]);
		G.add_edge(src, i + 1, sum);
	}
	for(int j = 1; j <= m; j++) {
		LL sum = 0;
		for(int i = 1; i <= n; i++) if(a[i][j] < 0) sum += std::abs(a[i][j]);
		G.add_edge(j + n + 1, dst, sum);
	}
	LL positive = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(a[i][j] > 0) positive += a[i][j];
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
		if(a[i][j] >= 0) G.add_edge(i + 1, j + n + 1, a[i][j]);
		else G.add_edge(j + n + 1, i + 1, LLINF);
	printf("%lld\n", positive - G.flow(src, dst));
	return 0;
}