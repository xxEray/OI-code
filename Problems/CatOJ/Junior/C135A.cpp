#include <cstdio>
#include <algorithm>
#include <cassert>

typedef long long LL;

const int N = 100 + 5;
const double eps = 1e-5;

int n1, n2, n3;

double f[3][N][N][N];

int main() {
	scanf("%d%d%d", &n1, &n2, &n3);
	for(int i = 1; i <= n1; i++) f[0][i][0][0] = 1;
	for(int i = 1; i <= n2; i++) f[1][0][i][0] = 1;
	for(int i = 1; i <= n3; i++) f[2][0][0][i] = 1;
	for(int i = 0; i <= n1; i++) for(int j = 0; j <= n2; j++) for(int k = 0; k <= n3; k++) if(i + j + k >= 2 && (bool)i + (bool)j + (bool)k >= 2) {
		for(int t = 0; t <= 2; t++) {
			double sum = (LL)i * j + (LL)j * k + (LL)k * i;
			if(j && k) (f[t][i][j][k] += f[t][i][j][k - 1] * ((LL)j * k / sum)); // s p
			if(k && i) (f[t][i][j][k] += f[t][i - 1][j][k] * ((LL)k * i / sum)); // p r
			if(i && j) (f[t][i][j][k] += f[t][i][j - 1][k] * ((LL)i * j / sum)); // r s
		}
		// printf("%d %d %d: %.2f %.2f %.2f\n", i, j, k, f[0][i][j][k], f[1][i][j][k], f[2][i][j][k]);
		// assert(std::abs(f[0][i][j][k] + f[1][i][j][k] + f[2][i][j][k] - 1) <= eps);
	}
	printf("%.6f %.6f %.6f\n", f[0][n1][n2][n3], f[1][n1][n2][n3], f[2][n1][n2][n3]);
	return 0;
}