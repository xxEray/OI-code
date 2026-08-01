#include <bits/stdc++.h>

typedef long long LL;

const int N = 1000 + 5;
const LL MOD = 998244353;

LL n;
int A, B;

LL g[N];

int main() {
#ifndef DEBUG
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld%d%d", &n, &A, &B);
		memset(g, 0, sizeof(g));
		g[A + B] = 1;
		LL sum = 1;
		int m;
		for(int i = A + B + 1; ; i++) {
			g[i] = g[i - A] + g[i - B];
			sum += g[i];
			if(sum >= n - 1) { m = i; break; }
		}
		for(int i = 1; i <= m; i++) g[i] %= MOD;
		LL ans = 0;
		sum = 0;
		// printf("g: "); for(int i = 1; i <= m; i++) printf("%lld ", g[i]); puts("");
		for(int i = 1; i < m; i++) (sum += g[i]) %= MOD, (ans += g[i] * i) %= MOD;
		(ans += (n - 1 - sum + MOD) % MOD * m) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
} /*
1
5 1 1
*/