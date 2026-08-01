#include <cstdio>
#include <algorithm>

const int N = 2000 + 5;

char s[N][N];
int n, m, Q;

int st[N][N], ans[N][N];
int copy[5 * N], tot[5 * N], suf[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j < n + 2 * m; j++) copy[j] = copy[j + 2];
		copy[n + 2 * m] = 0;
		for(int j = 1; j <= n; j++) {
			st[i][j] = st[i - 1][j];
			if(s[i][j] == 'O') st[i][j]++, copy[2 * m + j]++;
			if(i > m && s[i - m][j] == 'O') copy[j]--, st[i][j]--;
		}
		for(int j = 0; j <= n + 2 * m; j++) tot[j] = copy[j];
		int ret = 0;
		suf[n + 1] = 0;
		for(int j = n; j >= 1; j--) suf[j] = suf[j + 1] + st[i][j];
		for(int j = 1; j <= n + 2 * m; j++) ret += tot[j];
		for(int j = 1; j <= n; j++) {
			ret -= tot[j];
			ans[i][j] = ret - suf[j + 1];
		}
	}
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) printf("%d%c", ans[i][j], " \n"[j == n]);
	scanf("%d", &Q);
	while(Q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%d\n", ans[x][y]);
	}
	return 0;
}