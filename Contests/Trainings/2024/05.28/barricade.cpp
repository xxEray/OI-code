#include <bits/stdc++.h>

typedef long long LL;

const int N = 100 + 5;
const LL MOD = 998244353;

int n, b;
int a[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

int C[N][N];

LL f[N][N * N], g[N][N * N];

int main() {
	scanf("%d%d", &n, &b);
	for(int i = 0; i <= n; i++) C[i][0] = 1;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
	int sum = 0;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum += a[i];
	f[0][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = i; j >= 1; j--) for(int k = sum; k >= a[i]; k--) (f[j][k] += f[j - 1][k - a[i]]) %= MOD;
	for(int j = 1; j <= n; j++) for(int k = 0; k <= sum; k++) g[j][k] = f[j][k];
	LL ans = 0;
	if(sum - n * b < 0) ans = sum;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) for(int k = a[i]; k <= sum; k++) (f[j][k] += MOD - f[j - 1][k - a[i]]) %= MOD;
		LL E = 0;
		for(int j = 0; j < n; j++) {
			(E += n * inv(n - j)) %= MOD;
			for(int k = 0; k <= sum - a[i]; k++) if(k <= sum - n * b && k + a[i] > sum - n * b) {
				(ans += f[j][k] * inv(C[n][j]) % MOD * inv(n - j) % MOD * (E * b % MOD + (sum - k - a[i]))) %= MOD;
				// printf("i = %d, j = %d, k = %d, ans = %lld (f=%lld, E=%lld)\n", i, j, k, ans, f[j][k], E);
			}
		}
		for(int j = n; j >= 1; j--) for(int k = sum; k >= a[i]; k--) (f[j][k] += f[j - 1][k - a[i]]) %= MOD;
		for(int j = 1; j <= n; j++) for(int k = 0; k <= sum; k++) assert(f[j][k] == g[j][k]);
	}
	printf("%lld\n", ans);
	return 0;
}