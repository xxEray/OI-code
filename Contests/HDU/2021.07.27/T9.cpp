#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 100 + 5;

LL a[N][N], b[N][N];
int n;

std::pair<LL, LL> f[N][N][3];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) scanf("%lld", &a[i][j]);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) scanf("%lld", &b[i][j]);
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				for(int k = 0; k <= 2; k++) {
					if(i == 1 && j == 1) f[i][j][0] = f[i][j][1] = f[i][j][2] = {a[i][j], b[i][j]};
					else if(i == 1) f[i][j][0] = f[i][j][1] = f[i][j][2] = {f[i][j - 1][0].first + a[i][j], f[i][j - 1][0].second + b[i][j]};
					else if(j == 1) f[i][j][0] = f[i][j][1] = f[i][j][2] = {f[i - 1][j][0].first + a[i][j], f[i - 1][j][0].second + b[i][j]};
					else {
						std::pair<LL, LL> x, y;
						x = {f[i][j - 1][k].first + a[i][j], f[i][j - 1][k].second + b[i][j]};
						y = {f[i - 1][j][k].first + a[i][j], f[i - 1][j][k].second + b[i][j]};
						if(x.first != y.first) f[i][j][0] = (x.first > y.first ? x : y);
						else f[i][j][0] = (x.second > y.second ? x : y);
						x = {f[i][j - 1][k].first + a[i][j], f[i][j - 1][k].second + b[i][j]};
						y = {f[i - 1][j][k].first + a[i][j], f[i - 1][j][k].second + b[i][j]};
						if(x.second != y.second) f[i][j][1] = (x.second > y.second ? x : y);
						else f[i][j][1] = (x.first > y.first ? x : y);
						x = {f[i][j - 1][k].first + a[i][j], f[i][j - 1][k].second + b[i][j]};
						y = {f[i - 1][j][k].first + a[i][j], f[i - 1][j][k].second + b[i][j]};
						if(x.first * x.second != y.first * y.second)
							f[i][j][2] = (x.first * x.second > y.first * y.second ? x : y);
						else f[i][j][2] = (x > y ? x : y);
					}
				// printf("(%d, %d): (%lld,%lld), (%lld,%lld), (%lld,%lld)\n", i, j, f[i][j][0].first, f[i][j][0].second, f[i][j][1].first, f[i][j][1].second, f[i][j][2].first, f[i][j][2].second);
			}
		LL ans = std::max({f[n][n][0].first * f[n][n][0].second, f[n][n][1].first * f[n][n][1].second, f[n][n][2].first * f[n][n][2].second});
		printf("%lld\n", ans);
	}
	return 0;
}