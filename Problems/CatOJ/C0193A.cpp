#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 500 + 5;
const LL MOD = 998244353;

int n, len, K;
int a[N], b[N];

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

LL f[N][N];

int main() {
	scanf("%d%d%d", &len, &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++) if(b[i] == K) { K = i; break; }
	for(int i = 2; i <= n; i++) a[i] = b[i] - b[i - 1];
	a[1] = b[1] + len - b[n];
	for(int i = 1; i <= n; i++) b[i] = a[i];
	for(int i = n - K + 1; i <= n; i++) a[i] = b[i - (n - K + 1) + 1];
	for(int i = 1; i <= n - K; i++) a[i] = b[i + K];
	for(int i = 1; i <= n; i++) printf("%d ", a[i]);
	puts("");
	get_factorial(n);
	for(int i = 1; i <= n; i++) f[i][i] = 1;
	for(int len = 2; len <= n; len++) for(int i = 1; i + len - 1 <= n; i++) {
		int j = i + len - 1;
		LL sum = 0;
		for(int k = i; k < j; k++) sum += a[k], (f[i][j] += f[i][k] * f[k + 1][j] % MOD * C(j - i, k - i) % MOD * sum % MOD * inv(len) % MOD) %= MOD;
	}
	LL ans = 0, sum = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < i; j++)
			(ans += f[i][n] * qpow(sum * inv(len) % MOD, j) % MOD * C(n - i)) %= MOD;
		sum += a[i];
	}
	printf("%lld\n", ans);
	return 0;
}