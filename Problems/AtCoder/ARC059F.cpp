#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 5000 + 5;
const LL MOD = 1e9 + 7;

int n, m;
char s[N];

LL f[N][N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

int main() {
	scanf("%d%s", &n, s + 1);
	m = strlen(s + 1);
	f[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) (f[i][j] += f[i - 1][j - 1] * 2 + f[i - 1][j + 1]) %= MOD;
		(f[i][0] += f[i - 1][0] + f[i - 1][1]) %= MOD;
	}
	printf("%lld\n", f[n][m] * inv(qpow(2, m)) % MOD);
	return 0;
}