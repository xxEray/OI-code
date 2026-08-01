#include <bits/stdc++.h>

typedef long long LL;

const int N = 1000 + 5;

int n, ex, ey;

const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool vis[5][N];
int cnt, ans;
void dfs(int x, int y) {
	if(x == ex && y == ey) {
		(ans += (cnt == 3 * n - 1)) %= 998244353;
		return;
	}
	vis[x][y] = true, cnt++;
	for(int d = 0; d < 4; d++) {
		int dx = x + dir[d][0], dy = y + dir[d][1];
		if(1 <= dx && dx <= 3 && 1 <= dy && dy <= n && !vis[dx][dy]) dfs(dx, dy);
	}
	vis[x][y] = false, cnt--;
}

int main() {
	freopen("../traversal.in", "r", stdin);
	freopen("../traversal.ans", "w", stdout);
	int T; scanf("%d", &T);
	int out = 0;
	while(T--) {
		scanf("%d%d%d", &n, &ex, &ey);
		for(int i = 1; i <= 3; i++) for(int j = 1; j <= n; j++) vis[i][j] = false;
		ans = 0;
		dfs(1, 1);
		printf("%d\n", ans);
		out ^= ans;
	}
	// printf("%d\n", out);
	return 0;
}