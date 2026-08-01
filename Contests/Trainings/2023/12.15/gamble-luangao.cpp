#include <bits/stdc++.h>

typedef long long LL;

const int N = 1000 + 5;

int n;

int f[N][N];

int main() {
	scanf("%d", &n);
	int power = 1;
	for(int i = 1; i <= 2 * n - 1; i++) power *= 2;
	for(int i = n; i >= 0; i--) for(int j = n; j >= 0; j--)
		if(i == n || j == n) f[i][j] = (i == j ? 0 : (i == n ? -power : power));
		else f[i][j] = (f[i + 1][j] + f[i][j + 1]) / 2;
	for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) {
		printf("%c", f[i][j] > 0 ? '+' : (f[i][j] == 0 ? ' ' : '-'));
		for(int k = 2 * n - 1; k >= 0; k--) printf("%d", std::abs(f[i][j]) >> k & 1);
		printf("%c", " \n"[j == n]);
	}
	return 0;
}