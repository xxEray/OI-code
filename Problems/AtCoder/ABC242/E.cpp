#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 998244353;

char s[N];
char tmp[N];
int n;

LL f[N][2];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%s", &n, s + 1);
		int m = (n + 1) >> 1;
		for(int i = 1; i <= m; i++) tmp[i] = s[i], tmp[n - i + 1] = s[i];
		tmp[n + 1] = '\0';
		for(int i = 0; i <= m; i++) f[i][0] = f[i][1] = 0;
		f[0][1] = 1;
		for(int i = 1; i <= m; i++) {
			(f[i][0] += f[i - 1][0] * 26 % MOD) %= MOD;
			(f[i][0] += f[i - 1][1] * (s[i] - 'A') % MOD) %= MOD;
			(f[i][1] += f[i - 1][1]) %= MOD;
		}
		printf("%lld\n", ((strcmp(tmp + 1, s + 1) <= 0) + f[m][0]) % MOD);
	}
	return 0;
}