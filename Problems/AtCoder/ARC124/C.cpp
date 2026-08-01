#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long long LL;

const int N = 50 + 5;

LL a[N][2];
int n;

LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }
LL lcm(LL a, LL b) { return a / gcd(a, b) * b; }

LL calc(LL x, LL y) {
	for(int i = 1; i <= n; i++)
		if((a[i][0] % x || a[i][1] % y) && (a[i][1] % x || a[i][0] % y))
			return 1;
	return lcm(x, y);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &a[i][0], &a[i][1]);
	LL ans = 1;
	for(LL i = 1; i * i <= a[1][0]; i++) {
		if(a[1][0] % i) continue;
		for(LL j = 1; j * j <= a[1][1]; j++) {
			if(a[1][1] % j) continue;
			ans = std::max(ans, calc(i, j));
			ans = std::max(ans, calc(i, a[1][1] / j));
			ans = std::max(ans, calc(a[1][0] / i, j));
			ans = std::max(ans, calc(a[1][0] / i, a[1][1] / j));
		}
	}
	printf("%lld\n", ans);
	return 0;} /*
1020
*/