#include <bits/stdc++.h>

typedef long long LL;

const int N = 400 + 5;

int n, m;
int a[N][N], w1[N][N], w2[N][N];

namespace Subtask45 {
	bool check() {
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(!a[i][j]) return false;
		return true;
	}
	void main() {
		LL ans = 0;
		for(int i = 1; i <= n; i++) ans += w1[i][0] + w1[i][m];
		for(int j = 1; j <= m; j++) ans += w2[0][j] + w2[n][j];
		printf("%lld\n", ans);
	}
}

int main() {
#ifndef DEBUG
	freopen("oxygen.in", "r", stdin);
	freopen("oxygen.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; i++) for(int j = 0; j <= m; j++) scanf("%d", &w1[i][j]);
	for(int i = 0; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &w2[i][j]);
	if(Subtask45::check()) Subtask45::main();
	return 0;
} /*
3 3
1 1 1
1 1 1
1 1 1
1 4 9 4
1 6 6 6
1 2 2 9
1 1 1
4 4 4
2 4 2
6 6 6
*/