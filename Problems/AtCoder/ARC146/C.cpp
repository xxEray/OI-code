#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

LL n;
LL f[N][2];

int main() {
	scanf("%lld", &n);
	f[0][0] = 1, f[0][1] = 1;
	for(int i = 1; i <= n; i++) {
		f[i][0] = (f[i - 1][0] * f[i - 1][0] + f[i - 1][1] * f[i - 1][1] - f[i - 1][0] + 1) % MOD;
		f[i][1] = (f[i - 1][0] * f[i - 1][1] + f[i - 1][1] * f[i - 1][0]) % MOD;
	}
	printf("%lld\n", (f[n][0] + f[n][1]) % MOD);
	return 0;
}