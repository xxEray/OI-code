#include <bits/stdc++.h>

typedef long long LL;

const int N = 20 + 3;
const int MAXS = (1 << 20) + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m, K;
LL a[N];
struct Edge { int to; LL w; int wid; };
std::vector<Edge> from[N];

LL dis[N][N];
LL valp[N][N], vals[N][N];

LL f[MAXS][N];

LL sum = 0;
void solve(int st) {
	memset(f, 0x3f, sizeof(f));
	f[0][st] = 0;
	int U = (1 << K) - 1;
	for(int s = 0; s <= U; s++) {
		for(int i = 0; i < n; i++) {
			LL val = LLINF;
			for(int j = 0; j < K; j++) {
				if(s >> j & 1) val = std::min(val, f[s ^ (1 << j)][i]);
				valp[i][j] = val;
			}
			val = LLINF;
			for(int j = K - 1; j >= 0; j--) {
				if(s >> j & 1) val = std::min(val, f[s ^ (1 << j)][i] - a[j]);
				vals[i][j] = val;
			}
		}
		for(int i = 0; i < n; i++) for(auto [j, w, wid] : from[i]) {
			if(wid) f[s][i] = std::min(f[s][i], valp[j][wid - 1]);
			if(wid < K) f[s][i] = std::min(f[s][i], vals[j][wid] + w);
		}
		for(int i = 0; i < n; i++) for(int j = 0; j < n; j++)
			f[s][i] = std::min(f[s][i], f[s][j] + dis[j][i]);
	}
	for(int i = st + 1; i < n; i++) {
		LL mn = LLINF;
		for(int s = 0; s <= U; s++) mn = std::min(mn, f[s][i]);
		sum += mn;
	}
}

int main() {
#ifndef DEBUG
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) dis[i][j] = (i == j ? 0LL : LLINF);
	for(int i = 1; i <= m; i++) {
		int u, v; LL w;
		scanf("%d%d%lld", &u, &v, &w);
		from[v].push_back({u, w, 0}), from[u].push_back({v, w, 0});
		dis[u][v] = dis[v][u] = w;
	}
	for(int i = 0; i < K; i++) scanf("%lld", &a[i]);
	std::sort(a, a + K, std::greater<LL>());
	K = std::min(K, n - 1);
	for(int v = 0; v < n; v++)
		for(auto &[u, w, wid] : from[v])
			while(wid < K && a[wid] >= w) wid++;
	for(int k = 0; k < n; k++) for(int i = 0; i < n; i++) for(int j = 0; j < n; j++)
		dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
	for(int i = 0; i < n; i++) solve(i);
	printf("%lld\n", sum);
	return 0;
} /*
3 3 3
0 1 3
1 2 3
2 0 7
2 2 2
*/