#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

const LL pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};

LL n, K;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld", &n, &K);
		if(n <= 30 && (1 << n) < K) { puts("-1"); continue; }
		int bit = 0, dig = 0;
		do { dig++; } while(pow10[dig] <= K);
		// printf("dig = %d\n", dig);
		LL binom = 1;
		LL cn = 1, cK = K - pow10[dig - 1] + 1;
		LL ans = 0;
		while(dig) {
			LL mn = std::min(cn, cK);
			ans += mn * bit * dig;
			cn -= mn, cK -= mn;
			if(cn == 0) {
				bit++;
				binom *= (n - bit + 1), binom /= bit; // C(n, bit)
				cn = binom;
			}
			if(cK == 0) {
				dig--;
				cK = pow10[dig] - pow10[dig - 1];
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}