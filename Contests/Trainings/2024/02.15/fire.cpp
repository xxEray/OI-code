#include <bits/stdc++.h>

const long long MOD = 998244353;
const int inv3 = (MOD + 1) / 3;

int main() {
#ifndef DEBUG
	freopen("fire.in", "r", stdin);
	freopen("fire.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		int n, t;
		scanf("%d%d", &n, &t);
		if(n == 1) {
			scanf("%*d%*d");
			printf("%lld\n", 4LL * t % MOD * (t + 1) % MOD * (2 * t + 1) % MOD * inv3 % MOD);
		}
	}
	return 0;
}