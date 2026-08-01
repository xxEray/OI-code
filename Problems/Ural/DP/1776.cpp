#include <cstdio>

const int N = 400 + 5;

int n;

double f[N][N];

int main() {
	scanf("%d", &n);
	n -= 2;
	for(int i = 0; i <= n; i++)
		for(int j = i; j <= n; j++)
			f[i][j] = 1;
	for(int i = 3; i <= n; i++)
		for(int j = 1; j <= i - 1; j++) {
			f[i][j] = f[i][j - 1];
			for(int k = 1; k <= i; k++) {
				double ret = 0;
				ret += (f[k - 1][j - 1] - f[k - 1][j - 2]) * f[i - k][j - 1];
				ret += (f[i - k][j - 1] - f[i - k][j - 2]) * f[k - 1][j - 1];
				ret -= (f[k - 1][j - 1] - f[k - 1][j - 2]) * (f[i - k][j - 1] - f[i - k][j - 2]);
				f[i][j] += ret / i;
			}
		}
	double ans = 0;
	for(int i = 1; i <= n; i++)
		ans += (f[n][i] - f[n][i - 1]) * i * 10;
	printf("%.7lf\n", ans);
	return 0;
} /*
17
68.3998769
*/