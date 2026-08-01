#include <bits/stdc++.h>

typedef long long LL;

const int N = 100 + 5;

int n, m, mod;
struct Edge { int u, v; } edge[N];

int d[N], nxt[N];
int val[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }

int main() {
#ifndef DEBUG
	freopen("garakuta.in", "r", stdin);
	freopen("garakuta.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &mod);
	for(int i = 1; i <= m; i++) scanf("%d%d", &edge[i].u, &edge[i].v);
	int U = (1 << m) - 1;
	LL ans = 0;
	for(int s = 0; s <= U; s++) {
		for(int i = 1; i <= n; i++) d[i] = 0;
		for(int i = 1; i <= m; i++) if(s >> (i - 1) & 1) d[edge[i].u]++, nxt[edge[i].u] = edge[i].v;
		bool flag = true;
		for(int i = 1; i <= n; i++) flag &= (d[i] == 1);
		if(!flag) continue;
		int cnt = 0;
		for(int i = 1; i <= n; i++) val[i] = -1;
		for(int i = 1; i <= n; i++) if(val[i] == -1) {
			// printf("i = %d\n", i);
			val[i] = 0;
			int c = 0, j;
			for(j = nxt[i]; val[j] == -1; j = nxt[j]) val[j] = ++c;
			if(val[j] != -2) {
				cnt++, flag &= (c - val[j] + 1) & 1;
				// printf("j = %d, nxt[j] = %d\n", j, nxt[j]);
			}
			for(int k = i; val[k] != -2; k = nxt[k]) val[k] = -2;
		}
		if(!flag) continue;
		// printf("valid: %d (cnt=%d)\n", s, cnt);
		(ans += qpow(2, cnt)) %= mod;
	}
	printf("%lld\n", ans);
	return 0;
}