#include <cstdio>
#include <algorithm>

const int N = 1000 + 5;
const int LOG2_N = 10 + 2;

int n, m;

int C[N][LOG2_N];

int dp(int x, int y) {
	int ret = 0;
	for(int i = 0; i <= x; i++) {
		ret += C[y][i];
		if(ret > 1001) ret = 1001;
	}
	return ret - 1; // f(i, j) = dp[i][j] + 1，所以要减一
}

int main() {
	for(int i = 0; i <= 1000; i++) C[i][0] = 1;
	for(int i = 1; i <= 1000; i++)
		for(int j = 1; j <= 10; j++) {
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
			if(C[i][j] > 1001) C[i][j] = 1001;
		}
	while(scanf("%d%d", &m, &n) == 2 && (m || n)) {
		m = std::min(m, 10);
		int l = 1, r = 1000;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(dp(m, mid) < n) l = mid + 1;
			else r = mid;
		}
		printf("%d\n", l);
	}
	return 0;
}