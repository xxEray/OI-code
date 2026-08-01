#include <bits/stdc++.h>

typedef long long LL;

const int N = 7000 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m, K;
std::vector<std::pair<int, int>> vct[N];

LL f[N][N];
LL g[N];

int main() {
	scanf("%d%d%d", &n, &K, &m);
	for(int i = 1; i <= n; i++) { int x, y, z; scanf("%d%d%d", &x, &y, &z); vct[x].emplace_back(y % m, z); }
	for(int i = 0; i <= K; i++) for(int j = 0; j < m; j++) f[i][j] = LLINF;
	f[0][0] = 0;
	for(int i = 1; i <= K; i++) for(auto [w, v] : vct[i]) for(int j = 0; j < m; j++)
		f[i][(j + w) % m] = std::min(f[i][(j + w) % m], f[i - 1][j] + v);
	for(int i = 1; i < m; i++) g[i] = f[K][i];
	for(int _ = 1; _ <= 15; _++)
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < i; j++) g[i] = std::min(g[i], g[i - j] + g[j]);
			for(int j = i; j < m; j++) g[i] = std::min(g[i], g[i - j + m] + g[j]);
		}
	for(int i = 0; i < m; i++) printf("%lld\n", g[i] >= LLINF / 2 ? -1LL : g[i]);
	return 0;
}