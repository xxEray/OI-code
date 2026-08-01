#include <bits/stdc++.h>

const int N = 4e4 + 5;
const int M = 11;
const int MAXS = (1 << 9) + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int e[N][13];

int f[M][MAXS], g[M][MAXS];
int val[M];

void chkmin(int &x, int y) { if(y < x) x = y; }

int main() {
#ifndef DEBUG
	freopen("stairs.in", "r", stdin);
	freopen("stairs.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++) for(int j = 1; j <= m; j++) {
		char s[20];
		scanf("%s", s);
		for(int k = 0; k < m; k++) if(s[k] == '1') e[i][j] |= (1 << k);
	}
	int U = (1 << m) - 1;
	for(int i = 0; i <= m; i++) for(int s = 0; s <= U; s++) f[i][s] = n + 1;
	long long ans = 0;
	for(int i = n; i >= 1; i--) {
		for(int j = 0; j <= m; j++) for(int s = 0; s <= U; s++) g[j][s] = f[j][s], f[j][s] = n + 1;
		for(int s = 0; s <= U; s++) {
			int t = 0;
			for(int j = 1; j <= m; j++) if(s >> (j - 1) & 1) t |= e[i][j];
			for(int j = 0; j <= m; j++) chkmin(f[j][s], g[j][t]);
		}
		for(int s = 0; s <= U; s++) for(int j = __builtin_popcount(s); j <= m; j++) chkmin(f[j][s], i);
		for(int j = 1; j <= m; j++) for(int k = 0; k < m; k++) for(int s = 0; s <= U; s++) if(s >> k & 1) chkmin(f[j][s], f[j - 1][s ^ (1 << k)]);
		for(int j = 0; j <= m; j++) val[j] = std::max(i + 1, f[j][U]);
		for(int j = 1; j <= m; j++) ans += (long long)(val[j - 1] - val[j]) * j;
	}
	printf("%lld\n", ans);
	return 0;
}