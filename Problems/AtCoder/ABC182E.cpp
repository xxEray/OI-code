#include <cstdio>
#include <algorithm>

const int N = 1500 + 5;
const int CNT = 5e5 + 5;

int n, m, k1, k2;

int mark1[N][N], mark2[N][N];

std::pair<int, int> light[CNT];

int main() {
	std::scanf("%d%d%d%d", &n, &m, &k1, &k2);
	for(int i = 1; i <= k1; i++) std::scanf("%d%d", &light[i].first, &light[i].second);
	for(int i = 1; i <= k2; i++) {
		int x, y;
		std::scanf("%d%d", &x, &y);
		mark1[x][y] = mark2[x][y] = 2;
	}
	for(int i = 1; i <= k1; i++) {
		int x = light[i].first, y = light[i].second;
		if(mark1[x][y]) continue;
		for(int j = x; j <= n; j++)
			if(mark1[j][y] == 2) break;
			else mark1[j][y] = 1;
		for(int j = x; j >= 1; j--)
			if(mark1[j][y] == 2) break;
			else mark1[j][y] = 1;
	}
	for(int i = 1; i <= k1; i++) {
		int x = light[i].first, y = light[i].second;
		if(mark2[x][y]) continue;
		for(int j = y; j <= m; j++)
			if(mark2[x][j] == 2) break;
			else mark2[x][j] = 1;
		for(int j = y; j >= 1; j--)
			if(mark2[x][j] == 2) break;
			else mark2[x][j] = 1;
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			ans += (mark1[i][j] == 1 || mark2[i][j] == 1);
	std::printf("%d\n", ans);
	return 0;
}