#include <cstdio>
#include <algorithm>

typedef long long LL;
const int N = 2000 + 5;
const LL MOD = 998244353;

int n, m, K;
int a[N];

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

int cnt[N];
LL f[N];

int main() {
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), cnt[a[i]]++;
	get_factorial(std::max(n, m));
	int sum = 0;
	for(int i = 1; i <= m; i++) {
		sum += cnt[i];
		for(int j = K; j <= n; j++) if(j - sum >= 0 && j - sum <= cnt[0])
			(f[i] += C(cnt[0], j - sum) * qpow(i, j - sum) % MOD * qpow(m - i, cnt[0] - (j - sum)) % MOD) %= MOD;
	}
	// for(int i = 1; i <= m; i++) printf("f[%d] = %lld\n", i, f[i]);
	LL ans = 0;
	for(int i = 1; i <= m; i++) (ans += (f[i] - f[i - 1] + MOD) * i % MOD) %= MOD;
	printf("%lld\n", ans * qpow(inv(m), cnt[0]) % MOD);
	return 0;
}