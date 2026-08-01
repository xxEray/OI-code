#include <bits/stdc++.h>

typedef long long LL;

const int N = 3000 + 5;
const LL MOD = 998244353;

int n, m;
int a[N], b[N];

int f[N][N];
bool vis[N];

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int main() {
#ifndef DEBUG
	freopen("fail.in", "r", stdin);
	freopen("fail.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	get_factorial(n);
	f[0][0] = f[1][1] = 1;
	for(int i = 2; i <= n; i++) for(int j = 1; j <= i; j++) f[i][j] = ((LL)f[i - 1][j] * (i - 1) + f[i - 1][j - 1]) % MOD;
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= i; j++) printf("f[%d][%d] = %d\n", i, j, f[i][j]);
	LL ans = f[n][m];
	for(int i = 1; i <= n; i++) vis[i] = false;
	int mx = 0, rest = m;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j < a[i]; j++) if(!vis[j] && rest - (j > mx) >= 0 && std::max(mx, j) - i >= 0 && n - std::max(mx, j) >= 0)
			(ans += MOD - f[n - std::max(mx, j)][rest - (j > mx)] * fac[std::max(mx, j) - i] % MOD * C(n - i, std::max(mx, j) - i) % MOD) %= MOD;
		vis[a[i]] = true;
		if(a[i] > mx) rest--;
		mx = std::max(mx, a[i]);
	}
	for(int i = 1; i <= n; i++) vis[i] = false;
	mx = 0, rest = m;
	for(int i = 1; i <= n; i++) {
		for(int j = n; j > b[i]; j--) if(!vis[j])
			(ans += MOD - f[n - std::max(mx, j)][rest - (j > mx)] * fac[std::max(mx, j) - i] % MOD * C(n - i, std::max(mx, j) - i) % MOD) %= MOD;
		vis[b[i]] = true;
		if(b[i] > mx) rest--;
		mx = std::max(mx, b[i]);
	}
	printf("%lld\n", ans);
	return 0;
} /*
5 3
1 4 2 3 5
4 2 3 5 1
*/