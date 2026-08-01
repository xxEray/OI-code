#include <bits/stdc++.h>

typedef long double LD;

const int N = 10 + 5;
const int M = 45 + 4;
const int MAXS = (1 << 10) + 5;

int n, m;
int eu[M], ev[M];
int e[N];

int g[MAXS][MAXS], cnt[MAXS];
LD C[M << 1][M << 1], fac[M << 1];
LD f[M][MAXS];
LD tmp[MAXS];

int main() {
	scanf("%d%d", &n, &m);
	C[0][0] = 1, fac[0] = 1;
	for(int i = 1; i <= 2 * m; i++) C[i][0] = 1, fac[i] = fac[i - 1] * i;
	for(int i = 1; i <= 2 * m; i++) for(int j = 1; j <= i; j++) C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); eu[i] = u, ev[i] = v; e[u] |= (1 << (v - 1)), e[v] |= (1 << (u - 1)); }
	int U = (1 << n) - 1;
	for(int s = 0; s <= U; s++)
		for(int i = 1; i <= m; i++)
			if((s >> (eu[i] - 1) & 1) && (s >> (ev[i] - 1) & 1)) cnt[s]++;
	// for(int s = 0; s <= U; s++) printf("cnt[%d] = %d\n", s, cnt[s]);
	for(int s = 0; s <= U; s++)
		for(int t = ~s & U; ; t = (t - 1) & (~s & U)) {
			for(int i = 1; i <= m; i++)
				if((s >> (eu[i] - 1) & 1) && (t >> (ev[i] - 1) & 1)) g[s][t]++;
				else if((t >> (eu[i] - 1) & 1) && (s >> (ev[i] - 1) & 1)) g[s][t]++;
			// if(g[s][t]) printf("g[%d][%d] = %d\n", s, t, g[s][t]);
			if(!t) break;
		}
	for(int i = 1; i <= n; i++) f[0][1 << (i - 1)] = 1;
	for(int s = 0; s <= U; s++) {
		for(int i = 0; i <= m; i++) tmp[i] = 0;
		for(int t = s; ; t = (t - 1) & s) {
			int t_ = s ^ t;
			for(int j = 0; j <= m; j++) for(int k = 0; k <= m - j - 1; k++) tmp[j + k + 1] += f[j][t_] * f[k][t] * g[t_][t] * C[j + k][j];
			if(!t) break;
		}
		// if(s == 3) printf("tmp[1] = %.6Lf\n", tmp[1]);
		for(int i = 0; i <= cnt[s]; i++) for(int j = (s == U ? i : 0); j <= i; j++) f[i][s] += tmp[j] / 2 * C[cnt[s] - j][i - j] * fac[i - j];
	}
	// for(int s = 0; s <= U; s++) for(int i = 0; i <= m; i++) printf("f[%d][%d] = %.6Lf\n", i, s, f[i][s]);
	LD ans = 0;
	for(int i = n - 1; i <= m; i++) (ans += (LD)i / (m + 1) * (f[i][U] * fac[m - i] / fac[m]));
	printf("%.7lf\n", (double)ans);
	return 0;
} /*
3 3
1 2
2 3
3 1 
*/