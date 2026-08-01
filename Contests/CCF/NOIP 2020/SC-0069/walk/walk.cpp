#include <bits/stdc++.h>

const int N = 1000 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int walk[N][3];
int w[30];
int n, m;

int pre[N][30];
int mxpre[30], mnpre[30];

inline bool all0() {
	for(int i = 1; i <= m; i++) if(pre[n][i]) return false;
	for(int i = 1; i <= m; i++) if(mxpre[i] - mnpre[i] > w[i]) return false;
	return true;
}

int x[12], cpx[N];
int cnt = 0;
void dfs(int now) {
	if(now <= m) { for(int i = 1; i <= w[now]; i++) x[now] = i, dfs(now + 1); return; }
	for(int i = 1; i <= m; i++) cpx[i] = x[i];
	while(true) {
		bool flag = true;
		for(int j = 1; j <= m; j++) flag &= (1 <= x[j] + mnpre[j] && x[j] + mxpre[j] <= w[j]);
		if(flag) { cnt = (cnt + n) % MOD; for(int j = 1; j <= m; j++) x[j] += pre[n][j]; }
		else break;
	}
	for(int i = 1; i <= n; i++) {
		x[walk[i][0]] += walk[i][1];
		cnt = (cnt + 1) % MOD;
		if(x[walk[i][0]] < 1 || x[walk[i][0]] > w[walk[i][0]]) break;
	}
	for(int i = 1; i <= m; i++) x[i] = cpx[i];
}

int main() {
#ifndef DEBUG
	std::freopen("walk.in", "r", stdin);
	std::freopen("walk.out", "w", stdout);
#endif
	std::scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) std::scanf("%d", &w[i]);
	for(int i = 1; i <= n; i++) {
		std::scanf("%d%d", &walk[i][0], &walk[i][1]);
		for(int j = 1; j <= m; j++) pre[i][j] = pre[i - 1][j] + (walk[i][0] == j) * walk[i][1];
	}
	for(int i = 1; i <= m; i++) mxpre[i] = -INF, mnpre[i] = INF;
	for(int i = 0; i <= n; i++)
		for(int j = 1; j <= m; j++)
			mxpre[j] = std::max(mxpre[j], pre[i][j]),
			mnpre[j] = std::min(mnpre[j], pre[i][j]);
//	for(int i = 1; i <= m; i++) std::printf("mnpre[%d] = %d, mxpre[%d] = %d\n", i, mnpre[i], i, mxpre[i]);
	if(n > 100 || all0()) { std::printf("-1\n"); return 0; }
	dfs(1);
	std::printf("%d\n", cnt);
	return 0;
} /*
5 4
6 8 6 5
3 1
2 1
1 1
2 1
2 -1
*/
