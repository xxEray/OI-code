#include <cstdio>
#include <algorithm>

typedef long long LL;

const LL MOD = 998244353;
const LL inv2 = (MOD + 1) / 2;

LL f(LL x, LL y) { return (x - y) % MOD * ((x - y + 1) % MOD) % MOD * inv2 % MOD; }

int main() {
	LL n;
	scanf("%lld", &n);
	LL digit = 1, ans = 0;
	while(digit * 10 > 0 && (digit *= 10) <= n) (ans += f(digit - 1, digit / 10 - 1)) %= MOD;
	digit /= 10;
	// printf("digit = %lld\n", digit);
	(ans += f(n, digit - 1)) %= MOD;
	printf("%lld\n", (LL)ans);
	return 0;
}