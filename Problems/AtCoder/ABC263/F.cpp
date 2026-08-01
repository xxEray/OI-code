#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2000 + 5;
const LL MOD = 998244353;

LL n, m, K;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

LL fac[N], inv[N], S[N][N];
void preprocess(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	inv[1] = 1;
	for(int i = 2; i <= mx; i++) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
	S[0][0] = 1;
	for(int i = 1; i <= mx; i++)
		for(int j = 1; j <= i; j++)
			S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j] % MOD) % MOD;
}

int main() {
	preprocess(2000);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld%lld", &n, &m, &K);
		LL invm = qpow(m, MOD - 2);
		LL ans = 0, power = 1, qp1 = 1, qp2 = qpow(m, n);
		for(int i = 0; i <= std::min(n, K); i++) {
			// power = C(n, i)
			// qp1 = ((m+1)/2)^i
			// qp2 = m^(n-i)
			if(i) {
				(power *= (n - i + 1) * inv[i] % MOD) %= MOD;
				(qp1 *= (m + 1) / 2) %= MOD;
				(qp2 *= invm) %= MOD;
			}
			(ans += S[K][i] * fac[i] % MOD * power % MOD * qp1 % MOD * qp2 % MOD) %= MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}