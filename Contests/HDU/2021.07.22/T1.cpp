#include <cstdio>

const int MOD = 1e9 + 7;
const int inv2 = (MOD + 1) / 2;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		long long n;
		scanf("%lld", &n);
		n %= MOD;
		printf("%lld\n", 8LL * (n * (n - 1) % MOD * inv2 % MOD) % MOD * (n * (n - 1) % MOD * inv2 % MOD) % MOD);
	}
	return 0;
}