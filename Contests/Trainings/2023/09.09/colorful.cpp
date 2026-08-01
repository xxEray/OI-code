#include <bits/stdc++.h>

typedef long long LL;

const int N = 200 + 5;
const int MAXS = (1 << 14) + 5;
const LL MOD = 998244353;

int n, m, K;
int a[N];
std::vector<int> to[N];

int f[N][MAXS], g[N][MAXS];

void mod(int &x) { (x >= MOD) && (x -= MOD); }

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

int main() {
#ifndef DEBUG
	freopen("colorful.in", "r", stdin);
	freopen("colorful.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[u].push_back(v), to[v].push_back(u); }
	int U = (1 << K) - 1;
	for(int i = 1; i <= n; i++) f[i][(1 << (a[i] - 1))] = 1;
	for(int s = 0; s <= U; s++) {
		for(int u = 1; u <= n; u++) if(s >> (a[u] - 1) & 1) {
			int mn = 1;
			while(mn == a[u] || (~s >> (mn - 1) & 1)) mn++;
			int ns = s & ~(1 << (a[u] - 1)) & ~(1 << (mn - 1));
			for(int t = ns; ; t = (t - 1) & ns) {
				int nt = t | (1 << (mn - 1));
				mod(f[u][s] += (LL)g[u][nt] * f[u][s ^ nt] % MOD);
				if(!t) break;
			}
		}
		for(int u = 1; u <= n; u++) if(s >> (a[u] - 1) & 1)
			for(int v : to[u]) if(~s >> (a[v] - 1) & 1)
				mod(g[v][s] += f[u][s]);
	}
	// for(int i = 1; i <= n; i++) for(int s = 0; s <= U; s++) if(f[i][s]) printf("f[%d][%d] = %d\n", i, s, f[i][s]);
	// for(int i = 1; i <= n; i++) for(int s = 0; s <= U; s++) if(g[i][s]) printf("g[%d][%d] = %d\n", i, s, g[i][s]);
	LL ans = 0;
	for(int i = 1; i <= n; i++) (ans += f[i][U]) %= MOD;
	printf("%lld\n", ans * qpow(K, MOD - 2) % MOD);
	return 0;
} /*
6 8 4
4 2 1 2 3 4
1 2
2 3
3 4
5 3
6 3
1 6
1 5
5 4
*/