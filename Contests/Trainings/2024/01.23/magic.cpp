#include <bits/stdc++.h>

typedef long long LL;

const LL MOD = 998244353;

char s[25];
int n;
LL K;

LL f[2][25][61][41][21][21];
LL g[61][41][21][21];

LL power2[61], power3[41], power5[21], power7[21];

int main() {
#ifndef DEBUG
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
#endif
	scanf("%s%lld", s + 1, &K);
	n = strlen(s + 1);
	for(int i = 0; i < n; i++) f[i == 0][i][0][0][0][0] = 1;
	for(int i = 0; i < n; i++) for(int k2 = 0; k2 <= 54; k2++) for(int k3 = 0; k3 <= 36; k3++) for(int k5 = 0; k5 <= 18; k5++) for(int k7 = 0; k7 <= 18; k7++) {
		(f[0][i + 1][k2][k3][k5][k7] += f[0][i][k2][k3][k5][k7]) %= MOD; // 1
		(f[0][i + 1][k2 + 1][k3][k5][k7] += f[0][i][k2][k3][k5][k7]) %= MOD; // 2
		(f[0][i + 1][k2][k3 + 1][k5][k7] += f[0][i][k2][k3][k5][k7]) %= MOD; // 3
		(f[0][i + 1][k2 + 2][k3][k5][k7] += f[0][i][k2][k3][k5][k7]) %= MOD; // 4
		(f[0][i + 1][k2][k3][k5 + 1][k7] += f[0][i][k2][k3][k5][k7]) %= MOD; // 5
		(f[0][i + 1][k2 + 1][k3 + 1][k5][k7] += f[0][i][k2][k3][k5][k7]) %= MOD; // 6
		(f[0][i + 1][k2][k3][k5][k7 + 1] += f[0][i][k2][k3][k5][k7]) %= MOD; // 7
		(f[0][i + 1][k2 + 3][k3][k5][k7] += f[0][i][k2][k3][k5][k7]) %= MOD; // 8
		(f[0][i + 1][k2][k3 + 2][k5][k7] += f[0][i][k2][k3][k5][k7]) %= MOD; // 9
		if(s[i + 1] >= '1') (f[s[i + 1] == '1'][i + 1][k2][k3][k5][k7] += f[1][i][k2][k3][k5][k7]) %= MOD; // 1
		if(s[i + 1] >= '2') (f[s[i + 1] == '2'][i + 1][k2 + 1][k3][k5][k7] += f[1][i][k2][k3][k5][k7]) %= MOD; // 2
		if(s[i + 1] >= '3') (f[s[i + 1] == '3'][i + 1][k2][k3 + 1][k5][k7] += f[1][i][k2][k3][k5][k7]) %= MOD; // 3
		if(s[i + 1] >= '4') (f[s[i + 1] == '4'][i + 1][k2 + 2][k3][k5][k7] += f[1][i][k2][k3][k5][k7]) %= MOD; // 4
		if(s[i + 1] >= '5') (f[s[i + 1] == '5'][i + 1][k2][k3][k5 + 1][k7] += f[1][i][k2][k3][k5][k7]) %= MOD; // 5
		if(s[i + 1] >= '6') (f[s[i + 1] == '6'][i + 1][k2 + 1][k3 + 1][k5][k7] += f[1][i][k2][k3][k5][k7]) %= MOD; // 6
		if(s[i + 1] >= '7') (f[s[i + 1] == '7'][i + 1][k2][k3][k5][k7 + 1] += f[1][i][k2][k3][k5][k7]) %= MOD; // 7
		if(s[i + 1] >= '8') (f[s[i + 1] == '8'][i + 1][k2 + 3][k3][k5][k7] += f[1][i][k2][k3][k5][k7]) %= MOD; // 8
		if(s[i + 1] >= '9') (f[s[i + 1] == '9'][i + 1][k2][k3 + 2][k5][k7] += f[1][i][k2][k3][k5][k7]) %= MOD; // 9
	}
	for(int k2 = 54; k2 >= 0; k2--) for(int k3 = 36; k3 >= 0; k3--) for(int k5 = 18; k5 >= 0; k5--) for(int k7 = 18; k7 >= 0; k7--) {
		g[k2][k3][k5][k7] = f[0][n][k2][k3][k5][k7] + f[1][n][k2][k3][k5][k7];
		// if(g[k2][k3][k5][k7]) printf("g[%d][%d][%d][%d] = (originally) %lld\n", k2, k3, k5, k7, g[k2][k3][k5][k7]);
		g[k2][k3][k5][k7] += g[k2 + 1][k3][k5][k7] + g[k2][k3 + 1][k5][k7] + g[k2][k3][k5 + 1][k7] + g[k2][k3][k5][k7 + 1];
		g[k2][k3][k5][k7] -= g[k2 + 1][k3 + 1][k5][k7] + g[k2 + 1][k3][k5 + 1][k7] + g[k2 + 1][k3][k5][k7 + 1];
		g[k2][k3][k5][k7] -= g[k2][k3 + 1][k5 + 1][k7] + g[k2][k3 + 1][k5][k7 + 1] + g[k2][k3][k5 + 1][k7 + 1];
		g[k2][k3][k5][k7] += g[k2][k3 + 1][k5 + 1][k7 + 1] + g[k2 + 1][k3][k5 + 1][k7 + 1] + g[k2 + 1][k3 + 1][k5][k7 + 1] + g[k2 + 1][k3 + 1][k5 + 1][k7];
		g[k2][k3][k5][k7] -= g[k2 + 1][k3 + 1][k5 + 1][k7 + 1];
		g[k2][k3][k5][k7] = (g[k2][k3][k5][k7] % MOD + MOD) % MOD;
	}
	auto calc = [&](int k2, int k3, int k5, int k7) { return g[k2][k3][k5][k7] * g[k2][k3][k5][k7] % MOD; };
	LL ans = 0;
	for(int i = power2[0] = 1; i <= 54; i++) power2[i] = power2[i - 1] * 2;
	for(int i = power3[0] = 1; i <= 36; i++) power3[i] = power3[i - 1] * 3;
	for(int i = power5[0] = 1; i <= 18; i++) power5[i] = power5[i - 1] * 5;
	for(int i = power7[0] = 1; i <= 18; i++) power7[i] = power7[i - 1] * 7;
	for(int k2 = 0; k2 <= 54 && power2[k2] <= K; k2++)
		for(int k3 = 0; k3 <= 36 && power2[k2] * power3[k3] <= K; k3++)
			for(int k5 = 0; k5 <= 18 && power2[k2] * power3[k3] * power5[k5] <= K; k5++)
				for(int k7 = 0; k7 <= 18 && power2[k2] * power3[k3] * power5[k5] * power7[k7] <= K; k7++) {
					// LL val = power2[k2] * power3[k3] * power5[k5] * power7[k7];
					// printf("k2=%d, k3=%d, k5=%d, k7=%d, val=%lld\n", k2, k3, k5, k7, val);
					// if(calc(k2, k3, k5, k7)) printf("(%d, %d, %d, %d) = %lld\n", k2, k3, k5, k7, calc(k2, k3, k5, k7));
					ans += calc(k2, k3, k5, k7);
					ans -= calc(k2 + 1, k3, k5, k7) + calc(k2, k3 + 1, k5, k7) + calc(k2, k3, k5 + 1, k7) + calc(k2, k3, k5, k7 + 1);
					ans += calc(k2 + 1, k3 + 1, k5, k7) + calc(k2 + 1, k3, k5 + 1, k7) + calc(k2 + 1, k3, k5, k7 + 1);
					ans += calc(k2, k3 + 1, k5 + 1, k7) + calc(k2, k3 + 1, k5, k7 + 1) + calc(k2, k3, k5 + 1, k7 + 1);
					ans -= calc(k2, k3 + 1, k5 + 1, k7 + 1) + calc(k2 + 1, k3, k5 + 1, k7 + 1) + calc(k2 + 1, k3 + 1, k5, k7 + 1) + calc(k2 + 1, k3 + 1, k5 + 1, k7);
					ans += calc(k2 + 1, k3 + 1, k5 + 1, k7 + 1);
					ans = (ans % MOD + MOD) % MOD;
				}
	printf("%lld\n", ans);
	return 0;
}