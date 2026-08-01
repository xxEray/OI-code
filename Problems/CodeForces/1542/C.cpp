#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 1e9 + 7;

LL f[N];
LL n;

LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }
LL lcm(LL a, LL b) { return a / gcd(a, b) * b; }

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%lld", &n);
		LL sum = 0, lc1 = 1, lc2 = 1;
		for(int i = 1; i <= 44; i++) {
			lc2 = lcm(lc2, i);
			(sum += i * (n / lc1 - n / lc2) % MOD) %= MOD;
			lc1 = lcm(lc1, i);
		}
		printf("%lld\n", sum);
	}
	return 0;
}