#include <bits/stdc++.h>

const int N = 3000 + 5;

int n;
int a[N][N], b[N][N], c[N][N], d[N][N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i <= n + 1; i++) for(int j = 0; j <= n + 1; j++) a[i][j] = b[i][j] = c[i][j] = d[i][j] = 0;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				scanf("%1d", &a[i][j]);
		int ans = 0;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++) {
				c[i][j] = c[i - 1][j - 1], d[i][j] = d[i - 1][j + 1];
				b[i][j] = b[i - 1][j] ^ c[i][j] ^ d[i][j];
				if(a[i][j] ^ b[i][j])
					b[i][j] ^= 1, c[i][j] ^= 1, d[i][j] ^= 1, ans++; // , printf("(%d, %d)\n", i, j);
			}
		printf("%d\n", ans);
	}
	return 0;
}