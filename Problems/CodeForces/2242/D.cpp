#include <bits/stdc++.h>

const int N = 5e3 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
char a[N], b[N];

int f[2][N][10];

int mod(int x) { return (x % 10 + 10) % 10; }
void chkmax(int &x, int y) { if(x < y) x = y; }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s%s", a + 1, b + 1);
		n = strlen(a + 1), m = strlen(b + 1);
		for(int i = 1; i <= n; i++) a[i] -= '0';
		for(int i = 1; i <= m; i++) b[i] -= '0';
		for(int i = 0; i <= 1; i++) for(int j = 0; j <= m; j++) memset(f[i][j], ~0x3f, sizeof(f[i][j]));
		f[0][0][0] = 0;
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j <= m; j++) memset(f[i & 1][j], ~0x3f, sizeof(f[i & 1][j]));
			for(int j = 1; j <= m; j++) {
				chkmax(f[i & 1][j][mod(a[i] - b[j])], f[~i & 1][j - 1][0] + 1);
				for(int k = 0; k < 10; k++) {
					chkmax(f[i & 1][j][k], f[~i & 1][j][mod(k - a[i])]);
					chkmax(f[i & 1][j][k], f[i & 1][j - 1][mod(k + b[j])]);
				}
				// if(f[i][j][0] >= 0) printf("f[%d][%d][0] = %d\n", i, j, f[i][j][0]);
			}
		}
		if(f[n & 1][m][0] < 0) puts("-1");
		else printf("%d\n", f[n & 1][m][0]);
	}
	return 0;
}