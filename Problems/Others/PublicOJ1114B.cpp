#include <cstdio>
#include <algorithm>

const int N = 1000 + 5;
const long double eps = 1e-12;

int n, m, p_;
long double p;

long double f[N][N];

bool check(long double x) {
	for(int i = 1; i <= n; i++) f[i][0] = 0;
	for(int i = 1; i <= m; i++) f[0][i] = x;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) f[i][j] = std::min(f[i][j - 1] * p + f[i - 1][j] * (1 - p) + 1, x);
	// printf("check %.6lf: %.6lf\n", x, f[n][m]);
	return std::abs(f[n][m] - x) <= eps;
}

int main() {
	scanf("%d%d%d", &n, &m, &p_);
	p = p_ / 100.0;
	double l = 0, r = 1e9;
	int cnt = 0;
	while(l + eps < r && ++cnt <= 100) {
		double mid = (l + r) / 2;
		if(check(mid)) l = mid;
		else r = mid;
	}
	printf("%.7lf\n", (double)l);
	return 0;
}