#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const int SQRT_N = 500;
const LL MOD = 998244353;
const LL inv2 = (MOD + 1) / 2;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int n, Q;

int x[N];
LL powinv2[N];
int sum1[SQRT_N][N], sum2[SQRT_N][N];

int main() {
	scanf("%d%d", &n, &Q);
	get_factorial(2 * n);
	int sqrtn = 0;
	while((long long)sqrtn * sqrtn < 2 * n) sqrtn++;
	powinv2[0] = 1;
	for(int i = 1; i <= 2 * n; i++) powinv2[i] = powinv2[i - 1] * inv2 % MOD;
	for(int j = 0; j <= sqrtn; j++) for(int i = n; i <= 2 * n; i++) sum1[j][i] = (sum1[j][i - 1] + powinv2[i] * C(i - 1 - j, n - 1)) % MOD;
	for(int j = 0; j <= sqrtn; j++) for(int i = n; i <= 2 * n; i++) sum2[j][i] = (sum2[j][i - 1] + powinv2[i] * C(i - 1 - j, n - 1 - j)) % MOD;
	while(Q--) {
		int m;
		scanf("%d", &m);
		for(int i = 1; i <= m; i++) scanf("%d", &x[i]);
		if(m <= sqrtn) {
			// printf("type1: ");
			LL ans = 0;
			for(int i = 1; i <= m; i++) (ans += sum1[i - 1][x[i] - 1] - sum1[i - 1][x[i - 1]] + MOD) %= MOD;
			if(x[m] < 2 * n) (ans += powinv2[x[m]] * C(x[m] - 1 - (m - 1), n - 1 - (m - 1)) % MOD) %= MOD;
			if(2 * n - 1 > x[m]) (ans += sum1[m][2 * n - 1] - sum1[m][x[m]] + MOD) %= MOD;
			if(2 * n - 1 > x[m]) (ans += sum2[m][2 * n - 1] - sum2[m][x[m]] + MOD) %= MOD;
			printf("%lld\n", 2 * ans % MOD);
		} else {
			// printf("type2: ");
			LL ans = 0;
			int cnt = 0, j = 1;
			for(int i = 1; i <= 2 * n - 1; i++)
				if(j <= m && x[j] == i) cnt++, j++;
				else (ans += powinv2[i] * C(i - 1 - cnt, n - 1) % MOD) %= MOD;
			if(x[m] < 2 * n) (ans += powinv2[x[m]] * C(x[m] - 1 - (m - 1), n - 1 - (m - 1)) % MOD) %= MOD;
			for(int i = x[m] + 1; i <= 2 * n - 1; i++) (ans += powinv2[i] * C(i - 1 - m, n - 1 - m) % MOD) %= MOD;
			printf("%lld\n", 2 * ans % MOD);
		}
	}
	return 0;
}