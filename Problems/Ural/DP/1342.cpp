#include <cstdio>
#include <algorithm>

const int N = 1000 + 5;
const double DINF = 0x3f3f3f3f3f3f3f3f;

double top[N], start[N], add[N];
int n, m;

double f[N][N];

#define total(a, b, c) (((a) + (b)) * (c) / 2)

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lf%lf%lf", &top[i], &start[i], &add[i]), add[i] = (start[i] - add[i]) / (top[i] - 1);
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= m; j++)
			f[i][j] = DINF;
	f[0][0] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= m; j++)
			for(int k = 0; k <= top[i]; k++)
				f[i][j] = std::min(f[i][j], f[i - 1][j - k] + total(start[i], start[i] - (k - 1) * add[i], k));
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			printf("f[%d][%d] = %.2lf\n", i, j, f[i][j]);
	if(std::abs(f[n][m] - DINF) > 1e-8) printf("Minimum possible cost: %.2lf\n", f[n][m]);
	else
		for(int i = m - 1; i >= 0; i--)
			if(std::abs(f[n][i] - DINF) > 1e-8) {
				printf("Maximum possible amount: %d\nMinimum possible cost: %.2lf\n", i, f[n][i]);
				break;
			}
	return 0;
}