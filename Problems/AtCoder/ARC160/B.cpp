#include <bits/stdc++.h>

typedef long long LL;

const LL MOD = 998244353;

int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		LL ans = 0;
		for(int i = 1; i <= n; ) {
			int j = n / (n / i);
			int k = std::min(i, n / i);
			(ans += (LL)(j - i + 1) * k % MOD * (k + 1) * 3 % MOD) %= MOD;
			(ans += MOD - (LL)(j - i + 1) * 3 % MOD * std::min(i, n / i) % MOD) %= MOD;
			i = j + 1;
		}
		for(int i = 1; (LL)i * i <= n; i++) {
			(ans += 1) %= MOD;
			(ans += MOD - 3 * std::min(i, n / i) % MOD) %= MOD;
		}
		printf("%lld\n", (long long)ans);
	}
	return 0;
}