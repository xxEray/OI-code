#include <cstdio>
#include <algorithm>

const int N = 100 + 5;
const int INF = 0x3f3f3f3f;

int a[N][N];
int n, m;

const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int cnt, mni, mxi, mnj, mxj;
bool vis[N][N];
bool check(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }
void dfs(int x, int y) {
	mni = std::min(mni, x), mxi = std::max(mxi, x);
	mnj = std::min(mnj, y), mxj = std::max(mxj, y);
	cnt++;
	vis[x][y] = true;
	for(int d = 0; d < 4; d++) {
		int tx = x + dir[d][0], ty = y + dir[d][1];
		if(check(tx, ty) && a[tx][ty] && !vis[tx][ty]) dfs(tx, ty);
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%1d", &a[i][j]), vis[i][j] = false;
		bool flag = false;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(!vis[i][j] && a[i][j]) {
			cnt = 0, mni = mnj = INF, mxi = mxj = -INF;
			dfs(i, j);
			// printf("mni = %d, mnj = %d, mxi = %d, mxj = %d, cnt = %d\n", mni, mnj, mxi, mxj, cnt);
			flag |= ((mxi - mni + 1) * (mxj - mnj + 1) != cnt);
		}
		puts(flag ? "No" : "Yes");
	}
	return 0;
}