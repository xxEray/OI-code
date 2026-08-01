#include <cstdio>
#include <algorithm>

typedef long long LL;
const int N = 200 + 5;
const int M = 10000 + 5;
const LL MOD = 1e9 + 7;

int n, m;
int w[N];

LL f[N][M];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &w[i]);
	std::sort(w + 1, w + n + 1, [&](int x, int y) { return x > y; });
	f[0][0] = 1;
	for(int i = 1; i <= n; i++) for(int j = 0; j <= m; j++) f[i][j] = (f[i - 1][j] + (j >= w[i] ? f[i - 1][j - w[i]] : 0)) % MOD;
	int sum = 0;
	LL ans = 0;
	for(int i = n; i >= 1; i--) {
		for(int j = std::max(sum, m - w[i] + 1); j <= m; j++) (ans += f[i - 1][j - sum]) %= MOD;
		sum += w[i];
	}
	if(m >= sum) puts("1");
	else printf("%lld\n", ans);
	return 0;
}