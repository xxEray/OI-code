#include <cstdio>
#include <algorithm>

const int N = 100 + 5;
const int INF = 0x3f3f3f3f;

int n, K, Q;
int a[N][N];

int dis[N][N];

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = (i == j ? 0 : (a[i][j] ? 1 : INF));
	for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
	for(int i = 1; i <= n; i++) {
		dis[i][i] = INF;
		for(int j = 1; j <= n; j++) if(i != j && a[j][i]) dis[i][i] = std::min(dis[i][i], dis[i][j] + dis[j][i]);
	}
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) printf("dis[%d][%d] = %d\n", i, j, dis[i][j]);
	scanf("%d", &Q);
	while(Q--) {
		long long s, t;
		scanf("%lld%lld", &s, &t);
		s %= n, t %= n;
		if(s == 0) s = n;
		if(t == 0) t = n;
		if(s != t) printf("%d\n", dis[s][t] == INF ? -1 : dis[s][t]);
		else if(a[s][t]) puts("1");
		else printf("%d\n", dis[s][t] == INF ? -1 : dis[s][t]);
	}
	return 0;
}