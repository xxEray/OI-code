#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 5e3 + 5;
const int INF = 0x3f3f3f3f;

char a[N], b[N];
int n, m;
int Tins, Tdel, Trpl, Tswp; // INSert, DELele, RePLace, SWaP
int f[N][N];
int pos1[N][300], pos2[N][300], last[N];

int main() {
#ifndef DEBUG
	freopen("street.in", "r", stdin);
	freopen("street.out", "w", stdout);
#endif
	scanf("%d%d%d%d", &Tins, &Tdel, &Trpl, &Tswp);
	scanf("%s%s", a + 1, b + 1);
	n = strlen(a + 1), m = strlen(b + 1);
	for(int i = 'a'; i <= 'z'; i++) last[i] = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 'a'; j <= 'z'; j++) pos1[i][j] = last[j];
		last[a[i]] = i;
	}
	for(int i = 'a'; i <= 'z'; i++) last[i] = 0;
	for(int i = 1; i <= m; i++) {
		for(int j = 'a'; j <= 'z'; j++) pos2[i][j] = last[j];
		last[b[i]] = i;
	}
	// for(int i = 1; i <= std::max(n, m); i++)
	// 	for(int j = 'a'; j <= 'z'; j++)
	// 		if(pos1[i][j] || pos2[i][j])
	// 			printf("pos1[%d] = %d, pos2[%d] = %d\n", i, pos1[i][j], i, pos2[i][j]);
	for(int i = 0; i <= n; i++) for(int j = 0; j <= m; j++) f[i][j] = INF;
	f[0][0] = 0;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= m; j++) {
			if(j) f[i][j] = std::min(f[i][j], f[i][j - 1] + Tins);
			if(i) f[i][j] = std::min(f[i][j], f[i - 1][j] + Tdel);
			if(i && j) f[i][j] = std::min(f[i][j], f[i - 1][j - 1] + (a[i] == b[j] ? 0 : Trpl));
			int p1 = pos1[i][b[j]], p2 = pos2[j][a[i]];
			if(p1 && p2) f[i][j] = std::min(f[i][j], f[p1 - 1][p2 - 1] + (i - p1 - 1) * Tdel + (j - p2 - 1) * Tins + Tswp);
		}
	// for(int i = 0; i <= n; i++) for(int j = 0; j <= m; j++) printf("f[%d][%d] = %d\n", i, j, f[i][j]);
	printf("%d\n", f[n][m]);
	return 0;
}