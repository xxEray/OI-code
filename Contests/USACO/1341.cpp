#include <bits/stdc++.h>

const int N = 750 + 5;

int n;
int a[N][N], b[N][N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) scanf("%1d", &a[i][j]);
	for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) {
		b[i][j] = a[i][j];
		for(int k = i + 1; k < j; k++) if(b[i][k]) b[i][j] ^= a[k][j];
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) ans += b[i][j];
	printf("%d\n", ans);
	return 0;
}