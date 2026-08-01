#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2000 + 5;
const LL MOD = 1e9 + 7;
const LL inv2 = (MOD + 1) / 2;

int n, m;
LL K;

LL f[N][N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%lld", &n, &m, &K);
		for(int i = 1; i <= n; i++) {
			f[i][0] = K * i % MOD;
			for(int j = 1; j <= n - m; j++)
				f[i][j] = (f[i - 1][j] + f[i - 1][j - 1]) % MOD * inv2 % MOD;
		}
		printf("%lld\n", f[n][n - m]);
	}
	return 0;
}