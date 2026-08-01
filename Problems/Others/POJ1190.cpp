#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long long LL;

const int M = 1e5 + 5;
const int N = 15 + 5;
const int INF = 0x3f3f3f3f;

int n, m;

int sum[N], sum2[N];
int sq[M];

int ans = INF;
void dfs(int i, int h, int r, int rest, int ret) {
	if(i > n + 1) return;
	if(i == n + 1) {
		if(rest) return;
		ans = std::min(ans, ret);
		return;
	}
	if(ret + sum2[n - i + 1] >= ans) return;
	if(rest < sum[n - i + 1]) return;
	if((LL)(r - 1) * (r - 1) * (h - 1) < rest / (n - i + 1)) return;
	// printf("dfs(%d, %d, %d, %d, %d)\n", i, h, r, rest, ret);
	for(int rr = std::min(sq[rest], r - 1); rr >= n - i + 1; rr--)
		for(int hh = std::min(rest / (rr * rr), h - 1); hh >= n - i + 1; hh--)
			dfs(i + 1, hh, rr, rest - rr * rr * hh, ret + 2 * rr * hh);
}

int main() {
	scanf("%d%d", &m, &n);
	if(n == 0) { puts("0"); return 0; }
	for(int i = 1, r = 1, h = 1; i <= n; i++, r++, h++) sum[i] = sum[i - 1] + r * r * h;
	for(int i = 1, r = 1, h = 1; i <= n; i++, r++, h++) sum2[i] = sum2[i - 1] + 2 * r * h;
	for(int i = 1; i <= m; i++) sq[i] = floor(sqrt((double)i) + 1e-8);
	for(int r = sq[m]; r >= n; r--)
		for(int h = m / (r * r); h >= n; h--)
			dfs(2, h, r, m - r * r * h, r * r + 2 * r * h);
	if(ans == INF) puts("0");
	else printf("%d\n", ans);
	return 0;
}