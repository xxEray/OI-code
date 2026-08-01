#include <cstdio>
#include <algorithm>

const int N = 5000 + 5;

int n, m;

void input() {
	int x, y;
	scanf("%d%d", &x, &y);
	m = y - x * 2;
	n = x * 3 - y;
}

double f[2][N][2];
void solve() {
	f[1][0][1] = 1;
	for(int i = 2; i <= n + m; i++) {
		int t = (i - 1) & 1;
		for(int j = 0; j <= std::min(i, m); j++) {
			if(j) f[i & 1][j][0] = f[t][j - 1][0] * (j - 1) / (i - 1) + (f[t][j - 1][1] + 1) * (i - j) / (i - 1);
			f[i & 1][j][1] = (f[t][j][0] + 1) * j / (i - 1) + f[t][j][1] * (i - j - 1) / (i - 1);
		}
	}
}

void output() {
	printf("%.6lf\n", f[(n + m) & 1][m][0] * m / (n + m) + f[(n + m) & 1][m][1] * n / (n + m));
}

int main() {
	input();
	solve();
	output();
	return 0;
}