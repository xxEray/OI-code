#include <cstdio>
#include <algorithm>
#include <deque>

typedef long long LL;

const int N = 1000 + 5;

LL a[N][N], presum[N][N];
int n, m;
int r1, c1, r2, c2;

LL sum(int x1, int y1, int x2, int y2) { return presum[x2][y2] - presum[x1 - 1][y2] - presum[x2][y1 - 1] + presum[x1 - 1][y1 - 1]; }

LL aoki[N][N], takahashi[N][N];

struct Max_Counter {
	std::deque<int> q;
	LL mx[N][N], tmp[N][N];
	void init(int r, int c) {
		for(int i = 1; i <= n; i++) {
			q.clear();
			for(int j = 1; j <= m; j++) {
				while(!q.empty() && q.front() < j - c + 1) q.pop_front();
				while(!q.empty() && aoki[i][q.back()] <= aoki[i][j]) q.pop_back();
				q.push_back(j);
				tmp[i][j] = aoki[i][q.front()];
				// printf("max (%d, %d ~ %d) = %lld\n", i, j - c + 1, j, tmp[i][j]);
			}
		}
		for(int j = 1; j <= m; j++) {
			q.clear();
			for(int i = 1; i <= n; i++) {
				while(!q.empty() && q.front() < i - r + 1) q.pop_front();
				while(!q.empty() && tmp[q.back()][j] <= tmp[i][j]) q.pop_back();
				q.push_back(i);
				mx[i][j] = tmp[q.front()][j];
			}
		}
	}
	LL max(int x2, int y2) { return mx[x2][y2]; }
} ST;

int main() {
	scanf("%d%d%d%d%d%d", &n, &m, &r1, &c1, &r2, &c2);
	r2 = std::min(r2, r1), c2 = std::min(c2, c1);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%lld", &a[i][j]), presum[i][j] = presum[i][j - 1] + presum[i - 1][j] - presum[i - 1][j - 1] + a[i][j];
	for(int i = r2; i <= n; i++) for(int j = c2; j <= m; j++) aoki[i][j] = sum(i - r2 + 1, j - c2 + 1, i, j);
	// puts(""); for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) printf("%2lld%c", aoki[i][j], " \n"[j == m]);
	ST.init(r1 - r2 + 1, c1 - c2 + 1);
	for(int i = r1; i <= n; i++) for(int j = c1; j <= m; j++) takahashi[i][j] = sum(i - r1 + 1, j - c1 + 1, i, j) - ST.max(i, j);
	LL ans = 0;
	for(int i = r1; i <= n; i++) for(int j = c1; j <= m; j++) ans = std::max(ans, takahashi[i][j]);
	printf("%lld\n", ans);
	return 0;
}