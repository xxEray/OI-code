#include <cstdio>
#include <algorithm>
#include <set>

typedef long long LL;

const int N = 8e5 + 5;
const LL MOD = 998244353;

int n, m;
int a[N];

int cnt[N];

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

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i <= n + m; i++) cnt[i] = 1;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), cnt[a[i]] = 0;
	for(int i = 1; i <= n + m; i++) cnt[i] += cnt[i - 1];
	get_factorial(2 * (n + m));
	LL ans = 0;
	for(int i = 0; i <= n + m; i++)
		if(cnt[i] != cnt[i + 1] && cnt[i] <= m)
			(ans += C((i + 1) + (m - cnt[i]) - 1, m - cnt[i])) %= MOD; // , printf("%d(%d) ans=%lld\n", i, cnt[i], ans);
	printf("%lld\n", ans);
	return 0;
}