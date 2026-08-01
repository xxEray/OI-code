#include <cstdio>
#include <algorithm>

const int N = 1000 + 5;

char s[N][N];
int n, m, Q;

bool end[N][N];

int main() {
	scanf("%d%d%d", &n, &m, &Q);
	int cell = 0;
	for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cell += s[i][j] == '*';
	int tmp = cell;
	int lastx = n, lasty = 0;
	int ans = 0;
	for(int j = 1; j <= m && tmp; j++) for(int i = 1; i <= n && tmp; i++) {
		end[i][j] = true, tmp--;
		ans += s[i][j] == '.';
		lastx = i, lasty = j;
	}
	while(Q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		if(s[x][y] == '.') {
			lastx++;
			if(lastx == n + 1) lasty++, lastx = 1;
			end[lastx][lasty] = true;
			if(s[lastx][lasty] == '*') ans--;
			if(!end[x][y]) ans++;
			s[x][y] = '*';
		} else {
			if(s[lastx][lasty] == '*') ans++;
			end[lastx][lasty] = false;
			lastx--;
			if(lastx == 0) lasty--, lastx = n;
			if(!end[x][y]) ans--;
			s[x][y] = '.';
		}
		printf("%d\n", ans);
	}
	return 0;
}