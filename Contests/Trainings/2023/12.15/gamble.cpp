#include <bits/stdc++.h>

typedef long long LL;

const int N = 1000 + 5;
const LL MOD = 1e9 + 7;
const LL inv2 = (MOD + 1) / 2;

int n;

LL f[N][N];

int main() {
#ifndef DEBUG
	freopen("gamble.in", "r", stdin);
	freopen("gamble.out", "w", stdout);
#endif
	scanf("%d", &n);
	LL power = 1;
	for(int i = 1; i <= 2 * n - 1; i++) (power *= 2) %= MOD;
	for(int i = n; i >= 0; i--) for(int j = n; j >= 0; j--)
		if(i == n || j == n) f[i][j] = (i == j ? 0 : (i == n ? MOD - power : power));
		else f[i][j] = (f[i + 1][j] + f[i][j + 1]) * inv2 % MOD;
	// for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) printf("%lld%c", f[i][j], " \n"[j == n]);
	LL last = 0;
	int x = 0, y = 0;
	while(x < n && y < n) {
		int winner;
		scanf("%d", &winner);
		if(winner == 0) x++;
		else y++;
		LL now = f[x][y];
		printf("%lld\n", (winner == 0 ? (last - now + MOD) % MOD : (now - last + MOD) % MOD));
		last = now;
	}
	return 0;
}