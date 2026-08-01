#include <bits/stdc++.h>

const int N = 500 + 5;

int n, m;
int pre[N][N];

int sum(int xl, int xr, int yl, int yr) { return pre[xr][yr] - pre[xl - 1][yr] - pre[xr][yl - 1] + pre[xl - 1][yl - 1]; }

int f[N][N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int l, r; scanf("%d%d", &l, &r); pre[l][r]++; }
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) pre[i][j] += pre[i - 1][j];
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) pre[i][j] += pre[i][j - 1];
	for(int len = 1; len <= n; len++)
		for(int i = 1; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			for(int k = i; k <= j; k++)
				f[i][j] = std::max(f[i][j], f[i][k - 1] + f[k + 1][j] + (bool)sum(i, k, k, j));
		}
	printf("%d\n", f[1][n]);
	return 0;
}