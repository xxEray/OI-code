#include <bits/stdc++.h>

typedef long long LL;

const int N = 2000 + 5;
const LL MOD = 998244353;

int n;
char s[N];

LL f[2][N];

int main() {
	scanf("%d%s", &n, s + 1);
	for(int j = 1; j <= n; j++) f[1][j] = j * (s[1] == 'o');
	for(int i = 2; i <= n; i++)
		for(int j = 1; j <= n - i + 1; j++)
		if(s[i] == 'o') {
			f[i & 1][j] = j * f[~i & 1][2] % MOD;
		} else {
			f[i & 1][j] = j * (f[~i & 1][j + 1] - f[~i & 1][2] + MOD) % MOD;
		}
	printf("%lld\n", f[n & 1][1]);
	return 0;
}