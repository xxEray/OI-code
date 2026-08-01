#include <cstdio>
#include <algorithm>

typedef long long LL;
const int N = 2000 + 5;
const LL MOD = 998244353;

int n, m;
int a[N];
struct Node { int p, q; } b[N];
int va[N][N], vb[N][N];

int pre[N];

LL f[N][N], dp[N];

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x, LL mod = MOD) { return qpow(x, mod - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int tmp[N];
void preprocess() {
	for(int i = 1; i <= n; i++) tmp[a[i]]++;
	for(int i = 1; i <= n; i++) if(a[i]) {
		for(int j = i - 1; j >= 0; j--) {
			va[i][j] = va[i][j + 1];
			if(j && a[j] == 0) va[i][j]++;
		}
		for(int j = pre[i]; ; j = pre[j]) {
			vb[i][j] = 0;
			for(int k = a[j]; k <= a[i]; k++) if(tmp[k] == 0) vb[i][j]++;
			if(!j) break;
		}
		// for(int j = 0; j <= i - 1; j++) printf("%d->%d: va=%d, vb=%d\n", j, i, va[i][j], vb[i][j]);
	}
}
LL solve(int x) {
	for(int i = 0; i <= n; i++) f[0][i] = f[i][0] = 1, dp[i] = 0;
	for(int i = 1; i <= m; i++) for(int j = 1; j <= m; j++) f[i][j] = (f[i - 1][j] + f[i][j - 1] + (x - 1) * f[i - 1][j - 1]) % MOD;
	dp[0] = 1;
	for(int i = 1; i <= n; i++) if(a[i])
		for(int j = pre[i]; ; j = pre[j]) {
			if((!j || a[j]) && a[j] < a[i]) (dp[i] += dp[j] * f[va[i][j]][vb[i][j]]) %= MOD;
			if(!j) break;
		}
	// printf("solve(%d) = %lld\n", x, dp[n]);
	return dp[n];
}
LL g[N], h[N];
LL ret[N];
void get_answer() {
	h[0] = 1;
	for(int i = 1; i <= m + 1; i++)
		for(int j = m; j >= 0; j--)
			h[j] = ((j ? h[j - 1] : 0) + (MOD - i) * h[j]) % MOD;
	for(int i = 1; i <= m + 1; i++) {
		LL val = ret[i];
		for(int j = 1; j <= m + 1; j++) if(j != i) (val *= inv(MOD + i - j)) %= MOD;
		for(int j = 0; j <= m; j++) h[j] = ((j ? h[j - 1] : 0) + MOD - h[j]) * inv(i) % MOD;
		for(int j = 0; j <= m; j++) (g[j] += h[j] * val) %= MOD;
		for(int j = m; j >= 0; j--) h[j] = ((j ? h[j - 1] : 0) + (MOD - i) * h[j]) % MOD;
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i].p);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i].q);
	std::sort(b + 1, b + n + 1, [&](Node x, Node y) { return x.p < y.p; });
	for(int i = 1; i <= n; i++) a[i] = b[i].q;
	n++, a[n] = n;
	// printf("a: ");for(int i = 1; i <= n; i++) printf("%d ", a[i]); puts("");
	for(int i = 1; i <= n; i++) pre[i] = (a[i - 1] ? i - 1 : pre[i - 1]);
	get_factorial(n);
	for(int i = 1; i <= n; i++) m += (a[i] == 0);
	// m = n;
	preprocess();
	for(int i = 1; i <= m + 1; i++) ret[i] = solve(i);
	get_answer();
	// printf("g: "); for(int i = 0; i <= m; i++) printf("%lld ", g[i]); puts("");
	LL ans = 0;
	for(int i = 0; i <= m; i++) (ans += g[i] * fac[m - i]) %= MOD;
	printf("%lld\n", ans);
	return 0;
}