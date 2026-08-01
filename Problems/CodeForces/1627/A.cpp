#include <cstdio>
#include <algorithm>

const int N = 50 + 5;

char a[N][N];
int n, m, r, c;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d%d", &n, &m, &r, &c);
		for(int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
		int cnt = 0;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cnt += (a[i][j] == 'B');
		int cntb = 0;
		for(int i = 1; i <= n; i++) cntb += (a[i][c] == 'B');
		for(int j = 1; j <= m; j++) cntb += (a[r][j] == 'B');
		if(cnt == 0) puts("-1");
		else if(a[r][c] == 'B') puts("0");
		else if(cntb) puts("1");
		else puts("2");
	}
	return 0;
}