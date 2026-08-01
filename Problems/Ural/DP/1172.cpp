#include <cstdio>
#include <algorithm>

#include <biginteger>

const int N = 30 + 5;

int n;

BigInteger f[N][N][N][3];

int main() {
	scanf("%d", &n);
	f[1][0][0][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= n; j++)
			for(int k = 0; k <= n; k++) {
				f[i + 1][j][k][0] += (f[i][j][k][1] + f[i][j][k][2]) * (n - i);
				f[i][j + 1][k][1] += (f[i][j][k][0] + f[i][j][k][2]) * (n - j);
				f[i][j][k + 1][2] += (f[i][j][k][0] + f[i][j][k][1]) * (n - k);
			}
	std::cout << (f[n][n][n][1] + f[n][n][n][2]) / 2 << std::endl;
	return 0;
}