#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2000 + 5;

LL n, mod;

LL fac[100005];
LL qpow(LL a, LL b) { LL ret = 1; for(; b; b >>= 1) { if(b & 1) { (ret *= a) %= mod; } (a *= a) %= mod; } return ret; }
inline LL inv(LL x) { return qpow(x, mod - 2); }

int main() {
	scanf("%lld%lld", &n, &mod);
	fac[0] = 1;
	for(int i = 1; i <= 100000; i++) fac[i] = fac[i - 1] * i % mod;
	LL ans = 0;
	for(int i = 0; i <= n * 3; i++)
		for(int j = 0; j * 2 + i <= n * 3 && j <= i; j++) {
			int tmp = n * 3 - i - 2 * j;
			if(tmp % 3) continue;
			int k = tmp / 3;
			// printf("i = %d, j = %d, k = %d\n", i, j, k);
			(ans += fac[n * 3] * inv(fac[i]) % mod * inv(fac[j]) % mod * inv(fac[k]) % mod * inv(qpow(3, k)) % mod * inv(qpow(2, j)) % mod) %= mod;
		}
	printf("%lld\n", ans);
	return 0;
}