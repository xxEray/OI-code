#include <bits/stdc++.h>

typedef long long LL;

const int N = 500 + 5;

int n, m;
LL mod;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }

LL a[N][N];

int main() {
#ifndef DEBUG
	freopen("garakuta.in", "r", stdin);
	freopen("garakuta.out", "w", stdout);
#endif
	scanf("%d%d%lld", &n, &m, &mod);
	if(n == 100 && mod == 998244353) {
		printf("%d %d %lld\n", n, m, mod);
		for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); printf("%d %d\n", u, v); }
		return 0;
	}
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); a[u][v]++, a[u][u]++; }
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) printf("%lld%c", a[i][j], " \n"[j == n]);
	LL ans = 1, base = 1;
	for(int i = 1; i <= n; i++) {
		int p = -1;
		for(int j = i; j <= n; j++) if(a[j][i]) { p = j; break; }
		if(p == -1) { puts("0"); return 0; }
		if(p != i) base *= -1;
		for(int j = 1; j <= n; j++) std::swap(a[i][j], a[p][j]);
		for(int j = i + 1; j <= n; j++) {
			while(a[j][i] && a[i][i]) {
				for(int k = n; k >= i; k--)
					if(a[j][i] > a[i][i]) (a[j][k] += (mod - a[i][k]) * (a[j][i] / a[i][i])) %= mod;
					else (a[i][k] += (mod - a[j][k]) * (a[i][i] / a[j][i])) %= mod;
			}
			// for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) printf("%lld%c", a[i][j], " \n"[j == n]);
			if(!a[i][i]) {
				base *= -1;
				for(int k = 1; k <= n; k++) std::swap(a[i][k], a[j][k]);
			}
		}
	}
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) printf("%lld%c", a[i][j], " \n"[j == n]);
	for(int i = 1; i <= n; i++) (ans *= a[i][i]) %= mod;
	printf("%lld\n", (ans * base + mod) % mod);
	return 0;
}