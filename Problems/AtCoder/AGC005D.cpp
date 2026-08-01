#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 4000 + 5;
const LL MOD = 924844033;

int n, K;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

LL f[N][N][2];
bool cut[N];

int m, cnt, cx;
void preprocess() {
	int i = 0, j = 0;
	while(j < cx) cut[i] = true, i += m / cnt, j++;
	while(j < cnt) cut[i] = true, i += m / cnt + 1, j++;
	// for(i = 1; i <= m; i++) if(cut[i]) printf("%d ", i);
	// puts("");
}

int main() {
	scanf("%d%d", &n, &K);
	get_factorial(n);
	m = 2 * (n - K), cnt = std::min(2 * K, m), cx = cnt - m % cnt;
	preprocess();
	f[0][0][0] = 1;
	for(int i = 1; i <= m; i++) for(int j = 0; j <= m; j++) {
		(f[i][j][0] += f[i - 1][j][0] + f[i - 1][j][1]) %= MOD;
		if(j) (f[i][j][1] += f[i - 1][j - 1][0] + cut[i - 1] * f[i - 1][j - 1][1]) %= MOD;
	}
	LL ans = 0;
	for(int i = 0; i <= n; i++) (ans += qpow(MOD - 1, i) * (f[m][i][0] + f[m][i][1]) % MOD * fac[n - i] % MOD) %= MOD;
	printf("%lld\n", ans);
	return 0;
}