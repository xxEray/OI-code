#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 3e5 + 5;
const LL MOD = 998244353;
const LL inv2 = (MOD + 1) / 2;

int n;
int fa[N], dep[N];

LL f[N][30], g[N][30], h[N][30];

int main() {
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) scanf("%d", &fa[i]);
	dep[1] = 0;
	for(int i = 2; i <= n; i++) dep[i] = dep[fa[i]] + 1;
	for(int i = 1; i <= n; i++) {
		if(dep[i] <= 21) {
			f[i][0] = 1;
			int u = i, d = 0;
			while(fa[u]) {
				if(fa[fa[u]]) {
					(g[fa[fa[u]]][d + 2] += MOD - f[fa[u]][d + 1]) %= MOD;
					(h[fa[fa[u]]][d + 2] += MOD - f[fa[u]][d + 1] * f[fa[u]][d + 1] % MOD) %= MOD;
				}
				(g[fa[u]][d + 1] += f[u][d]) %= MOD;
				(h[fa[u]][d + 1] += f[u][d] * f[u][d]) %= MOD;
				f[fa[u]][d + 1] = ((g[fa[u]][d + 1] * g[fa[u]][d + 1] % MOD + MOD - h[fa[u]][d + 1]) % MOD * inv2) % MOD;
				u = fa[u], d++;
			}
		}
		LL ans = 0;
		for(int j = 0; j <= 21; j++) (ans += f[1][j]) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
}