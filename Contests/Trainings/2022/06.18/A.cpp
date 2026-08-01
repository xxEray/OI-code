#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e5 + 5;

int type[300];
char s[N];
int n;

#define isA(x) (type[(x)] >> 0 & 1)
#define isN(x) (type[(x)] >> 1 & 1)
#define isV(x) (type[(x)] >> 2 & 1)

bool f[N][2], g[N][2]; // 0 -> n.  1 -> adj.

int main() {
	// freopen("a.in", "r", stdin);
	// freopen("a.out", "w", stdout);
	int T; scanf("%d", &T);
	while(T--) {
		for(int i = 'a'; i <= 'z'; i++) scanf("%d", &type[i]);
		scanf("%s", s + 1);
		n = strlen(s + 1);
		f[1][0] = isN(s[1]), f[1][1] = isA(s[1]);
		for(int i = 2; i <= n; i++) {
			f[i][0] = (f[i - 1][0] || f[i - 1][1]) && isN(s[i]);
			f[i][1] = (f[i - 1][0] || f[i - 1][1]) && isA(s[i]);
		}
		g[n][0] = 0, g[n][1] = isN(s[n]);
		for(int i = n - 1; i >= 1; i--) {
			g[i][0] = (g[i + 1][0] || g[i + 1][1]) && isN(s[i]);
			g[i][1] = (g[i + 1][0] || g[i + 1][1]) && isA(s[i]);
		}
		bool flag = false;
		for(int i = 2; i < n; i++) flag |= f[i - 1][0] && isV(s[i]) && (g[i + 1][0] || g[i + 1][1]);
		puts(flag ? "Yes" : "No");
	}
	return 0;
} /*

*/