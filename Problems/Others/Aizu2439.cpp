#include <cstdio>
#include <algorithm>

typedef long long LL;
const int N = 200 + 5;
const LL MOD = 1e9 + 7;

int n;
int a[N];

LL f[N][N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) { char s[2]; scanf("%s", s); a[i] = (s[0] == '-' ? 0 : (s[0] == 'U' ? 1 : -1)); }
	f[0][0] = 1;
	for(int i = 1; i <= n; i++)
		if(a[i] == 0) {
			for(int j = 0; j <= i; j++) f[i][j] = f[i - 1][j];
		} else if(a[i] == 1) {
			for(int j = 1; j <= i; j++) (f[i][j] += f[i - 1][j] * j % MOD) %= MOD;
			for(int j = 0; j < i; j++) (f[i][j + 1] += f[i - 1][j]) %= MOD;
		} else if(a[i] == -1) {
			for(int j = 1; j <= i; j++) (f[i][j - 1] += f[i - 1][j] * j % MOD * j % MOD) %= MOD;
			for(int j = 1; j <= i; j++) (f[i][j] += f[i - 1][j] * j % MOD) %= MOD;
		}
	// for(int i = 1; i <= n; i++) for(int j = 0; j <= i; j++) if(f[i][j]) printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
	printf("%lld\n", f[n][0]);
	return 0;
}