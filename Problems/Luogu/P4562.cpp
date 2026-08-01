#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e7;
const LL MOD = 1e9 + 7;

int n, L, R;

bool ok[N];
int cnt = 0;
void preprocess() {
	for(int i = L; i <= R; i++) ok[i] = true;
	for(int i = L; i <= R; i++) if(ok[i]) {
		cnt++;
		for(int j = i + i; j <= R; j += i) ok[j] = false;
	}
}

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
	scanf("%d%d", &L, &R);
	n = R - L + 1;
	preprocess();
	// printf("cnt = %d\n", cnt);
	get_factorial(R);
	LL ans = 0;
	for(int i = cnt; i <= n; i++)
		(ans += (LL)i * cnt % MOD * C(n - cnt, i - cnt) % MOD * fac[i - 1] % MOD * fac[n - i] % MOD) %= MOD;
	printf("%lld\n", ans);
	return 0;
}