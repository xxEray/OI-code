#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1.5e7 + 5;
const LL MOD = 998244353;

LL n, A, B, C, sum;
LL fac[N], invfac[N];

LL qpow(LL a, LL b) { LL ret = 1; while(true) { if(b & 1) ret = ret * a % MOD; if(!(b >>= 1)) return ret; a = a * a % MOD; }}

int main() {
	scanf("%lld%lld%lld%lld", &n, &A, &B, &C);
	sum = A + B + C;
	fac[0] = 0;
	for(int i = 1; i <= 15000000; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[15000000] = qpow(fac[15000000], MOD - 2);
	for(int i = 15000000; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
	// ans = sum! / (A! * B! * C!) * C(sum + 1, n - 1)
	LL ret = fac[sum]
	return 0;
}