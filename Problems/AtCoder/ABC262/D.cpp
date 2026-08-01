#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 100 + 5;
const LL MOD = 998244353;

int a[N];
int n;

LL f[N][N][N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	LL ans = 0;
	for(int t = 1; t <= n; t++) {
		for(int i = 1; i <= n; i++) for(int j = 0; j <= n; j++) for(int k = 0; k < t; k++) f[i][j][k] = 0;
		f[0][0][0] = 1;
		for(int i = 1; i <= n; i++)
			for(int j = 0; j <= i; j++)
				for(int k = 0; k < t; k++) {
					(f[i][j][k] += f[i - 1][j][k]) %= MOD;
					if(j) (f[i][j][k] += f[i - 1][j - 1][(k - a[i] % t + t) % t]) %= MOD;
				}
		(ans += f[n][t][0]) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
}