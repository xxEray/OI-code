#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

char t[2][N], s[N][3];
int f[N][4];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%s%s", &n, t[0] + 1, t[1] + 1);
		for(int i = 1; i <= n; i++) s[i][1] = t[0][i], s[i][2] = t[1][i];
		for(int i = 1; i <= n; i++) f[i][0] = f[i][1] = f[i][2] = f[i][3] = INF;
		int rmost = 0;
		for(int i = 1; i <= n; i++) if(s[i][1] == '*' || s[i][2] == '*') rmost = i;
		for(int i = 1; i <= n; i++) {
			f[i][3] = std::min(f[i][3], f[i - 1][3] + 2);
			if(s[i][1] == '*') f[i][3] = std::min(f[i][3], f[i - 1][2] + 1);
			if(s[i][2] == '*') f[i][3] = std::min(f[i][3], f[i - 1][1] + 1);
			if(s[i][1] == '*' && s[i][2] == '*') f[i][3] = std::min(f[i][3], f[i - 1][0]);
			if(s[i][2] == '*') f[i][1] = f[i][3] + 1;
			else {
				f[i][1] = std::min(f[i][1], f[i][3] + 1);
				f[i][1] = std::min(f[i][1], f[i - 1][1] + 1);
				if(s[i][1] == '*') f[i][1] = std::min(f[i][1], f[i - 1][0]);
			}
			if(s[i][1] == '*') f[i][2] = f[i][3] + 1;
			else {
				f[i][2] = std::min(f[i][2], f[i][3] + 1);
				f[i][2] = std::min(f[i][2], f[i - 1][2] + 1);
				if(s[i][2] == '*') f[i][2] = std::min(f[i][2], f[i - 1][0]);
			}
			f[i][1] = std::min(f[i][1], f[i][2] + 1);
			f[i][2] = std::min(f[i][2], f[i][1] + 1);
			f[i][0] = std::min(f[i][0], f[i - 1][0]);
			if(s[i][1] == '*' || s[i][2] == '*') f[i][0] = INF;
		}
		printf("%d\n", std::min(f[rmost][1], f[rmost][2]));
	}
	return 0;
} /*
1
3
*.*
.*.
*/