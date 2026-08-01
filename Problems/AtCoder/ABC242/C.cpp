#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 998244353;

LL f[N][10];
int n;

int main() {
	scanf("%d", &n);
	for(int j = 1; j <= 9; j++) f[1][j] = 1;
	for(int i = 2; i <= n; i++) for(int j = 1; j <= 9; j++) {
		(f[i][j] += f[i - 1][j]) %= MOD;
		if(j + 1 <= 9) (f[i][j] += f[i - 1][j + 1]) %= MOD;
		if(j - 1 >= 1) (f[i][j] += f[i - 1][j - 1]) %= MOD;
	}
	LL ans = 0;
	for(int i = 1; i <= 9; i++) (ans += f[n][i]) %= MOD;
	printf("%lld\n", ans);
	return 0;
}