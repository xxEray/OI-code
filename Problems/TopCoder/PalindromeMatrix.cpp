#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
using std::string;
using std::vector;

const int N = 14 + 5;
const int INF = 0x3f3f3f3f;

int a[N][N];
int n, m;

int f[N][N], cost[N][5];

void chkmin(int &x, int y) { if(y < x) x = y; }

class PalindromeMatrix {
public:
	int minChange(vector<string> A, int rowCount, int columnCount) {
		n = A.size(), m = A[0].size();
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = A[i - 1][j - 1] - '0';
		int U = (1 << n) - 1;
		int ans = INF;
		for(int s = 0; s <= U; s++) {
			if(__builtin_popcount(s) < rowCount) continue;
			memset(cost, 0, sizeof(cost));
			memset(f, 0x3f, sizeof(f));
			for(int i = 1; i <= n / 2; i++)
				for(int j = 1; j <= m / 2; j++) {
					int i_ = n - i + 1, j_ = m - j + 1;
					int ri = s >> (i - 1) & 1, ri_ = s >> (i_ - 1) & 1;
					int tmp[5] = {INF, INF, INF, INF};
					for(int t = 0; t < 16; t++) {
						int x = t & 1, y = t >> 1 & 1, z = t >> 2 & 1, w = t >> 3 & 1;
						if(ri && (x != y)) continue;
						if(ri_ && (z != w)) continue;
						chkmin(tmp[(x == z) | ((y == w) << 1)], (x != a[i][j]) + (y != a[i][j_]) + (z != a[i_][j]) + (w != a[i_][j_]));
						chkmin(tmp[((y == w) << 1)], (x != a[i][j]) + (y != a[i][j_]) + (z != a[i_][j]) + (w != a[i_][j_]));
						chkmin(tmp[(x == z)], (x != a[i][j]) + (y != a[i][j_]) + (z != a[i_][j]) + (w != a[i_][j_]));
						chkmin(tmp[0], (x != a[i][j]) + (y != a[i][j_]) + (z != a[i_][j]) + (w != a[i_][j_]));
						// printf("tmp[%d] min= %d\n", (x == z) | ((y == w) << 1), (x != a[i][j]) + (y != a[i][j_]) + (z != a[i_][j]) + (w != a[i_][j_]));
					}
					// printf("i = %d, j = %d, tmp = %d, %d, %d, %d\n", i, j, tmp[0], tmp[1], tmp[2], tmp[3]);
					cost[j][0] += tmp[0], cost[j][1] += tmp[1], cost[j][2] += tmp[2], cost[j][3] += tmp[3];
					chkmin(cost[j][0], INF), chkmin(cost[j][1], INF), chkmin(cost[j][2], INF), chkmin(cost[j][3], INF);
				}
			f[0][0] = 0;
			// for(int i = 1; i <= m / 2; i++) for(int j = 0; j <= 3; j++) printf("cost[%d][%d] = %d\n", i, j, cost[i][j]);
			for(int i = 1; i <= m / 2; i++) for(int k = 0; k <= 3; k++)
				for(int j = __builtin_popcount(k); j <= m; j++) chkmin(f[i][j], f[i - 1][j - __builtin_popcount(k)] + cost[i][k]);
			for(int i = columnCount; i <= m; i++) chkmin(ans, f[m / 2][i]);
			// printf("s = %d, ans = %d\n", s, ans);
		}
		return ans;
	}
};

// int main() {
// 	PalindromeMatrix T;
// 	printf("%d\n", T.minChange({"0000"
// ,"1000"
// ,"1100"
// ,"1110"},
// 3,
// 2));
// 	return 0;
// }