#include <bits/stdc++.h>

const int N = 5e4 + 5;
const int B = 300;

int n, Q;
int nxt[2][17][N];

int go(int c, int step, int now) {
	for(int k = 0; k <= 16; k++) if(step >> k & 1) now = nxt[c][k][now];
	return now;
}
int f[2][B + 5][N];

int main() {
#ifndef DEBUG
	freopen("worm.in", "r", stdin);
	freopen("worm.out", "w", stdout);
#endif
	// printf("%.3f\n", (sizeof(nxt) + sizeof(f)) / 1024. / 1024);
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d%d", &nxt[0][0][i], &nxt[1][0][i]);
	nxt[0][0][n + 1] = nxt[1][0][n + 1] = n + 1;
	nxt[0][0][n + 2] = nxt[1][0][n + 2] = n + 2;
	for(int j = 1; j <= 16; j++)
		for(int i = 1; i <= n + 2; i++) {
			nxt[0][j][i] = nxt[0][j - 1][nxt[0][j - 1][i]];
			nxt[1][j][i] = nxt[1][j - 1][nxt[1][j - 1][i]];
		}
	for(int j = 1; j <= B; j++) {
		f[0][j][n + 1] = f[1][j][n + 1] = n + 1;
		f[0][j][n + 2] = f[1][j][n + 2] = n + 2;
	}
	for(int i = n; i >= 1; i--) {
		int now[2] = {i, i};
		for(int j = 1; j <= B; j++) {
			now[0] = nxt[0][0][now[0]], now[1] = nxt[1][0][now[1]];
			f[0][j][i] = f[1][j][now[0]], f[1][j][i] = f[0][j][now[1]];
		}
	}
	// fprintf(stderr, "time = %d\n", (int)clock());
	while(Q--) {
		int p, k, c;
		scanf("%d%d%d", &p, &k, &c);
		if(k <= B) printf("%d\n", f[c][k][p] - (n + 1));
		else {
			while(p <= n) p = go(c, k, p), c ^= 1;
			printf("%d\n", p - (n + 1));
		}
	}
	// fprintf(stderr, "time = %d\n", (int)clock());
	return 0;
}