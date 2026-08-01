#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 7e6 + 5;
const int MAXN = 7e6;
const LL MOD = 998244353;

LL n, A, B, C;

LL fac[N], invfac[N];
LL fA[N], fB[N], fC[N];

LL qpow(LL a, LL b) { LL ret = 1; while(true) { if(b & 1) ret = ret * a % MOD; if(!(b >>= 1)) return ret; a = a * a % MOD; } }
LL Combination(LL x, LL y) { return x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }

int main() {
	scanf("%lld%lld%lld%lld", &n, &A, &B, &C);
	fac[0] = 1;
	for(int i = 1; i <= MAXN; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[MAXN] = qpow(fac[MAXN], MOD - 2);
	for(int i = MAXN; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
	fA[0] = 1;
	for(int i = 1; i <= A; i++) fA[i] = fA[i - 1] * 2 % MOD;
	for(int i = A + 1; i <= n; i++) fA[i] = (2 * fA[i - 1] % MOD + MOD - Combination(i - 1, A)) % MOD;
	fB[0] = 1;
	for(int i = 1; i <= B; i++) fB[i] = fB[i - 1] * 2 % MOD;
	for(int i = B + 1; i <= n; i++) fB[i] = (2 * fB[i - 1] % MOD + MOD - Combination(i - 1, B)) % MOD;
	fC[0] = 1;
	for(int i = 1; i <= C; i++) fC[i] = fC[i - 1] * 2 % MOD;
	for(int i = C + 1; i <= n; i++) fC[i] = (2 * fC[i - 1] % MOD + MOD - Combination(i - 1, C)) % MOD;
	LL ans = 0;
	for(int i = 0; i <= n; i++) (ans += qpow(MOD - 1, n - i) * Combination(n, i) % MOD * fA[i] % MOD * fB[i] % MOD * fC[i] % MOD) %= MOD;
	printf("%lld\n", ans);
	return 0;
}