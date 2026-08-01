#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 100 + 5;

int a[N][N];
int n;

int sum[N][N][5];
int ans = 1;

void clear() {
	memset(sum, 0, sizeof(sum));
	memset(a, 0, sizeof(a));
	ans = 1;
}

void input() {
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			scanf("%d", &a[i][j]);
}

int totalf(int x1, int y1, int x2, int y2)
	{ return sum[x2][y2][0] - sum[x1 - 1][y2][0] - sum[x2][y1 - 1][0] + sum[x1 - 1][y1 - 1][0]; }
int totalc(int x, int y, int l) {
	int ret = 0;
	ret += sum[x + l / 2 - 1][y + l - 1][1] - sum[x - 1][y + l / 2][1] - totalf(1, y + l / 2 + 1, x - 1, y + l - 1);
	ret += sum[x + l / 2 - 1][y][2] - sum[x - 1][y + l / 2][2] - totalf(1, y, x - 1, y + l / 2 - 1);
	ret += sum[x + l / 2 + 1][y][3] - sum[x + l][y + l / 2][3] - totalf(x + l, y, n, y + l / 2 - 1);
	ret += sum[x + l / 2 + 1][y + l - 1][4] - sum[x + l][y + l / 2][4] - totalf(x + l, y + l / 2 + 1, n, y + l - 1);
	return ret;
}
inline bool check(int x, int y, int l) {
	int ret1 = totalf(x, y, x + l - 1, y + l - 1);
	int ret2 = totalc(x, y, l);
	return (ret1 == ret2 && ret1 == (l - 1) * (l / 2 + 1));
}

void preprocess() {
	// 0 = full, 1 = RU, 2 = LU, 3 = LD, 4 = RD
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			sum[i][j][0] = sum[i - 1][j][0] + sum[i][j - 1][0] - sum[i - 1][j - 1][0] + a[i][j];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			sum[i][j][1] = sum[i - 1][j - 1][1] + totalf(1, j, i, j);
	for(int i = 1; i <= n; i++)
		for(int j = n; j >= 1; j--)
			sum[i][j][2] = sum[i - 1][j + 1][2] + totalf(1, j, i, j);
	for(int i = n; i >= 1; i--)
		for(int j = n; j >= 1; j--)
			sum[i][j][3] = sum[i + 1][j + 1][3] + totalf(i, j, n, j);
	for(int i = n; i >= 1; i--)
		for(int j = 1; j <= n; j++)
			sum[i][j][4] = sum[i + 1][j - 1][4] + totalf(i, j, n, j);
}

void debug() {
	printf("sum 0:\n");
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			printf("%d%c", sum[i][j][0], j == n ? '\n' : ' ');
	printf("sum 1:\n");
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			printf("%d%c", sum[i][j][1], j == n ? '\n' : ' ');
	printf("sum 2:\n");
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			printf("%d%c", sum[i][j][2], j == n ? '\n' : ' ');
	printf("sum 3:\n");
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			printf("%d%c", sum[i][j][3], j == n ? '\n' : ' ');
	printf("sum 4:\n");
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			printf("%d%c", sum[i][j][4], j == n ? '\n' : ' ');
}

void solve() {
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			int limit = std::min(n - i + 1, n - j + 1);
			limit -= !(limit & 1);
			for(int k = ans + 2; k <= limit; k += 2)
				if(check(i, j, k)) ans = k;
		}
}

void output() {
	if(ans > 1) printf("%d\n", ans);
	else puts("No solution");
}

void case_test() {
	clear();
	input();
	preprocess();
	// debug();
	solve();
	output();
}

int main() {
	while(scanf("%d", &n) == 1 && n) case_test();
	return 0;
} /*
8
1 0 1 1 1 1 1 1
0 0 0 1 1 1 1 1
1 0 1 1 1 1 1 1
1 1 1 1 0 1 1 1
1 1 1 0 0 0 1 1
1 1 0 0 0 0 0 1
1 1 1 0 0 0 1 1
1 1 1 1 0 1 1 1
*/