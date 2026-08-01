#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

const int N = 5e5 + 5;

int a[5][N];
int n, Q;

int belong[5][N];
int cnt;
int lmost[3 * N], rmost[3 * N];
int midl[N], midr[N];
int zl[2][N], zr[2][N];
int sufl[N], prer[N];

const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool vis[5][N];
void dfs(int x, int y, int &lm, int &rm, int id) {
	belong[x][y] = id;
	vis[x][y] = true;
	lm = std::min(lm, y), rm = std::max(rm, y);
	for(int d = 0; d < 4; d++) {
		int dx = x + dir[d][0], dy = y + dir[d][1];
		if(1 <= dx && dx <= 3 && 1 <= dy && dy <= n && !vis[dx][dy] && a[dx][dy]) {
			dfs(dx, dy, lm, rm, id);
		}
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= 3; i++) for(int j = 1; j <= n; j++) scanf("%1d", &a[i][j]);
	midl[0] = 0, midr[n + 1] = n + 1;
	for(int i = 1; i <= n; i++) midl[i] = (a[2][i] ? i : midl[i - 1]);
	for(int i = n; i >= 1; i--) midr[i] = (a[2][i] ? i : midr[i + 1]);
	for(int i = 0; i <= n; i++) zl[0][i] = (!a[1][i] ? i + 1 : zl[0][i - 1]);
	for(int i = n + 1; i >= 1; i--) zr[0][i] = (!a[1][i] ? i - 1 : zr[0][i + 1]);
	for(int i = 0; i <= n; i++) zl[1][i] = (!a[3][i] ? i + 1 : zl[1][i - 1]);
	for(int i = n + 1; i >= 1; i--) zr[1][i] = (!a[3][i] ? i - 1 : zr[1][i + 1]);
	for(int i = 1; i <= 3; i++) for(int j = 1; j <= n; j++) if(a[i][j] && !vis[i][j])
		cnt++, lmost[cnt] = n + 1, rmost[cnt] = 0, dfs(i, j, lmost[cnt], rmost[cnt], cnt);
	for(int i = 1; i <= cnt; i++) sufl[lmost[i]]++, prer[rmost[i]]++;
	for(int i = n; i >= 1; i--) sufl[i] += sufl[i + 1];
	for(int i = 1; i <= n; i++) prer[i] += prer[i - 1];
	scanf("%d", &Q);
	while(Q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		int ans = cnt - prer[l - 1] - sufl[r + 1];
		// printf("\t\t\t%d -> ", ans);
		if(belong[1][l] && belong[1][l] == belong[3][l] && belong[1][r] == belong[3][r] && belong[1][l] == belong[1][r]) {
			if(zr[0][l] >= r && zr[1][l] >= r) {
				ans += (midr[l] > r);
			} else {
				ans += !(zr[0][l] >= midr[l] && zr[1][l] >= midr[l]) + !(zl[0][r] <= midl[r] && zl[1][r] <= midl[r]);
			}
		} else {
			if(belong[1][l] && belong[1][l] == belong[3][l]) {
				if(midr[l] > zr[0][l] || midr[l] > zr[1][l]) {
					// assert(midl[l] >= lmost[id]);
					ans++;
				}
			}
			if(belong[1][r] && belong[1][r] == belong[3][r]) {
				if(midl[r] < zl[0][r] || midl[r] < zl[1][r]) {
					// assert(midr[r] <= rmost[id]);
					ans++;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
} /*
16
0010111100110011
1011000100100010
1111101111111011
100
3 7
*/