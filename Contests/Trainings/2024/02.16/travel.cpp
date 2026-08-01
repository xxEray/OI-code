#include <bits/stdc++.h>

typedef long long LL;

const int N = 20 + 3;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m, K;
LL a[N];
LL dis[N][N];

LL ret[N][N];
int p[N];

int main() {
#ifndef DEBUG
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) ret[i][j] = dis[i][j] = (i == j ? 0LL : LLINF);
	for(int i = 1; i <= m; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); dis[u][v] = dis[v][u] = w; }
	for(int i = 0; i < K; i++) scanf("%lld", &a[i]);
	std::sort(a, a + K, std::greater<LL>());
	for(int i = 0; i < n; i++) p[i] = i + 1;
	do {
		std::vector<LL> vct;
		for(int i = 0; i < n - 1; i++) {
			if(dis[p[i] - 1][p[i + 1] - 1] == LLINF) break;
			vct.emplace_back(dis[p[i] - 1][p[i + 1] - 1]);
			for(int j = i; j && vct[j] > vct[j - 1]; j--) std::swap(vct[j], vct[j - 1]);
			LL sum = 0;
			for(int j = 0; j <= i; j++) sum += std::max(0LL, vct[j] - a[j]);
			ret[p[0] - 1][p[i + 1] - 1] = std::min(ret[p[0] - 1][p[i + 1] - 1], sum);
		}
	} while(std::next_permutation(p, p + n));
	LL ans = 0;
	for(int i = 0; i < n; i++) for(int j = i + 1; j < n; j++) ans += ret[i][j]; // , printf("%d -> %d = %lld\n", i, j, ret[i][j]);
	printf("%lld\n", ans);
	return 0;
}