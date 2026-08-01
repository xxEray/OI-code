#include <bits/stdc++.h>

#define clear(arr) memset((arr), 0, sizeof((arr)))

const int N = 1000 + 5;

int n, m;
char s[N], t[N];

int ss[N], st[N];
int f[N][N];

int main() {
#ifndef DEBUG
	freopen("irony.in", "r", stdin);
	freopen("irony.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		clear(s), clear(t), clear(ss), clear(st);
		scanf("%d%d%s%s", &n, &m, s + 1, t + 1);
		for(int i = 1; i <= n; i++) ss[i] = ss[i - 1] + (s[i] == '(' ? 1 : -1);
		for(int i = 1; i <= m; i++) st[i] = st[i - 1] + (t[i] == '(' ? 1 : -1);
		memset(f, 0x3f, sizeof(f));
		f[0][0] = 0;
		for(int i = 0; i <= n; i++) for(int j = 0; j <= m; j++) {
			int now = ss[i] + st[j] + f[i][j];
			if(i < n) {
				int nxt = now + (s[i + 1] == '(' ? 1 : -1);
				if(nxt < 0) f[i + 1][j] = std::min(f[i + 1][j], f[i][j] + 1);
				else f[i + 1][j] = std::min(f[i + 1][j], f[i][j]);
			}
			if(j < m) {
				int nxt = now + (t[j + 1] == '(' ? 1 : -1);
				if(nxt < 0) f[i][j + 1] = std::min(f[i][j + 1], f[i][j] + 1);
				else f[i][j + 1] = std::min(f[i][j + 1], f[i][j]);
			}
		}
		printf("%d\n", f[n][m] + (f[n][m] + ss[n] + st[m]));
	}
	return 0;
}