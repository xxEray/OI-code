#include <bits/stdc++.h>

typedef long long LL;

const int N = 500 + 5;
const int M = 1e5 + 5;
const LL MOD = 998244353;

int n, m, K;
struct Node { int x; LL w; } a[N];
bool operator<(Node x, Node y) { return x.x < y.x; }
struct Segment { int l, r; LL p; } b[M];

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { assert(x); return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

LL f[N][N], g[N][N], s[N][N], sg[N];

int main() {
// #ifndef DEBUG
// 	freopen("probability.in", "r", stdin);
// 	freopen("probability.out", "w", stdout);
// #endif
	freopen("ex_probability2.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &K);
	get_factorial(n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i].x);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i].w);
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= m; i++) {
		scanf("%d%d%lld", &b[i].l, &b[i].r, &b[i].p);
		b[i].l = std::lower_bound(a + 1, a + n + 1, (Node){b[i].l, 0}) - a;
		b[i].r = std::upper_bound(a + 1, a + n + 1, (Node){b[i].r, 0}) - a - 1;
		(b[i].p *= inv(100)) %= MOD;
	}
	// printf("a: "); for(int i = 1; i <= n; i++) printf("(%d, %lld) ", a[i].x, a[i].w); puts("");
	// printf("b:\n"); for(int i = 1; i <= m; i++) printf("(%d, %d, %lld)\n", b[i].l, b[i].r, b[i].p);
	f[0][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= K; j++) {
			LL power = 1;
			for(int k = 0; k <= j; k++) {
				(f[i][j] += f[i - 1][j - k] * power % MOD * invfac[k] % MOD) %= MOD;
				(power *= a[i].w) %= MOD;
			}
		}
	// for(int i = 0; i <= K; i++) printf("f_%d = %lld\n", i, f[n][i]);
	for(int i = 0; i <= n + 1; i++) for(int j = i; j <= n + 1; j++) s[i][j] = 1;
	int lb = n + 1, rb = 0;
	for(int i = 1; i <= m; i++)
		if(b[i].p != 1) {
			for(int j = 0; j <= b[i].l - 1; j++)
				for(int k = b[i].r + 1; k <= n + 1; k++)
					(s[j][k] *= inv((MOD + 1 - b[i].p) % MOD)) %= MOD;
		} else {
			for(int j = 0; j <= n + 1; j++)
				for(int k = j; k <= n + 1; k++)
					if(j <= b[i].r && k >= b[i].l && !(j < b[i].l && k > b[i].r)) s[j][k] = 0;
		}
	// for(int i = 0; i <= n + 1; i++) for(int j = i; j <= n + 1; j++) printf("s(%d, %d) = %lld\n", i, j, s[i][j]);
	g[0][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= K; j++)
			for(int p = 0; p < i; p++) {
				LL power = 1;
				for(int q = 1; q <= j; q++) {
					(power *= a[i].w) %= MOD;
					(g[i][j] += power * invfac[q] % MOD * s[p][i] % MOD * g[p][j - q] % MOD) %= MOD;
				}
			}
	// for(int i = 0; i <= n; i++) for(int j = 0; j <= K; j++) printf("g[%d][%d] = %lld\n", i, j, g[i][j]);
	for(int i = 0; i <= n; i++) for(int j = 0; j <= K; j++) (sg[j] += g[i][j] * s[i][n + 1] % MOD) %= MOD;
	// for(int i = 0; i <= K; i++) printf("g_%d = %lld\n", i, sg[i]);
	LL prod = 1;
	for(int i = 1; i <= m; i++) if(b[i].p != 1) (prod *= (MOD + 1 - b[i].p) % MOD) %= MOD;
	LL ans = 0;
	for(int i = 0; i <= K; i++) (ans += qpow(MOD - 1, K - i) * f[n][i] % MOD * sg[K - i] % MOD * fac[K] % MOD * prod % MOD) %= MOD;
	printf("%lld\n", ans);
	return 0;
} /*
4 3 4
1 4 6 2
3 9 7 1
2 5 30
4 10 70
1 4 40
*/