#include <bits/stdc++.h>

typedef long long LL;

const int N = 400 + 5;

int n, K;
LL mod;

LL f[2][2][N][N], inv[N], pre[N];

int main() {
	scanf("%d%d%lld", &n, &K, &mod);
	inv[1] = 1;
	for(int i = 2; i <= n; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	for(int i = 1; i <= n; i++) {
		int t = i & 1, tr = t ^ 1;
		for(int j = 1; j <= i; j++) for(int k = j; k <= i; k++) f[0][i & 1][j][k] = f[1][i & 1][j][k] = 0;
		if(i == 1) f[1][1][1][1] = f[0][1][1][2] = 1;
		for(int j = 1; j <= i + 1; j++)
			for(int k = j; k <= i + 1; k++) {
				(f[0][t][j][k] += f[0][tr][j][k] * (k - j)) %= mod;
				(f[1][t][j][k] += f[0][tr][j][k]) %= mod;
				(f[1][t][j][k] += f[1][tr][j][k] * (k - j + 1)) %= mod;
				(f[1][t][k][k] += mod - f[1][tr][j][k]) %= mod;
				if(j < k) {
					(f[0][t][j][k] += f[0][tr][j][k - 1] * (k - j)) %= mod;
					(f[0][t][k - 1][k] += mod - f[1][tr][j][k - 1]) %= mod;
					(f[1][t][j][k] += f[1][tr][j][k - 1] * (k - j)) %= mod;
				}
			}
	}
	LL ans = 0;
	for(int i = 1; i <= n; i++) {
		LL comb = 1;
		for(int j = 1; j <= i; j++) (comb *= inv[j]) %= mod;
		for(int j = 0; j < i; j++) (comb *= K - j) %= mod;
		pre[i] = comb;
	}
	for(int j = 1; j <= n; j++) for(int k = j; k <= n; k++)
		(ans += pre[k] * f[1][n & 1][j][k]) %= mod;
	printf("%lld\n", ans);
	return 0;
} /*
3 4 998244353
*/