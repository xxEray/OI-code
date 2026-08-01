#include <bits/stdc++.h>

typedef long long LL;

const int N = 3000 + 5;
const LL MOD = 1e9 + 7;

int n, m;
struct Node { int val, type; } a[2 * N];

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
LL A(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

LL f[2][N][2];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); a[i].val = x, a[i].type = 1; }
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); a[i + n].val = x, a[i + n].type = 2; }
	std::sort(a + 1, a + 2 * n + 1, [&](Node x, Node y) { return x.val == y.val ? x.type < y.type : x.val < y.val; });
	f[0][0][1] = 1;
	for(int i = 1; i <= 2 * n; i++) {
		memset(f[i & 1], 0, sizeof(f[i & 1]));
		if(a[i].type == 1) {
			for(int j = 1; j <= n; j++) (f[i & 1][j][0] += f[~i & 1][j - 1][0]) %= MOD;
			for(int j = 0; j <= n; j++) (f[i & 1][j][0] += f[~i & 1][j][0] + f[~i & 1][j][1]) %= MOD;
			for(int j = 1; j <= n; j++) (f[i & 1][j][1] += f[~i & 1][j - 1][1]) %= MOD;
		} else {
			for(int j = 0; j < n; j++) (f[i & 1][j][0] += f[~i & 1][j + 1][0] * (j + 1)) %= MOD;
			for(int j = 0; j < n; j++) (f[i & 1][j][1] += f[~i & 1][j][1] + f[~i & 1][j + 1][1] * (j + 1)) %= MOD;
		}
	}
	printf("%lld\n", (f[0][0][0] + f[0][0][1]) % MOD);
	return 0;
}