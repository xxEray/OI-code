#include <bits/stdc++.h>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
char s[N], t[N];

int last[30], nxt[N][30], prenxt[N][30];

int main() {
#ifndef DEBUG
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif
	scanf("%s%s", s + 1, t + 1);
	n = strlen(s + 1), m = strlen(t + 1);
	for(int i = 1; i <= n; i++) s[i] -= 'a';
	for(int i = 1; i <= m; i++) t[i] -= 'a';
	for(int j = 0; j < 26; j++) last[j] = prenxt[m + 1][j] = nxt[m + 1][j] = m + 1;
	for(int i = m; i >= 0; i--) {
		if(i) last[t[i]] = i;
		for(int j = 0; j < 26; j++) nxt[i][j] = last[j];
		prenxt[i][0] = nxt[i][0];
		for(int j = 1; j < 26; j++) prenxt[i][j] = std::min(prenxt[i][j - 1], nxt[i][j]);
	}
	// for(int i = 0; i <= m; i++) for(int j = 0; j < 26; j++) printf("nxt[%d][%d] = %d,%d\n", i, j, nxt[i][j], prenxt[i][j]);
	int ans = INF;
	for(int i = 0, j = 0, w = 0; i < n; i++) {
		ans = std::min(ans, (s[i + 1] ? prenxt[j + 1][s[i + 1] - 1] - 1 : m) - j + w); // , printf("%d,%d: ans = %d, w = %d, nxt[%d][%d] = %d\n", i, j, ans, w, j + 1, s[i + 1] - 1, prenxt[j + 1][s[i + 1] - 1]);
		w += nxt[j + 1][s[i + 1]] - j - 1, j = nxt[j + 1][s[i + 1]];
		if(j > m) break;
	}
	printf("%d\n", ans == INF ? -1 : ans);
	return 0;
} /*
aaaaaaaaaa
haagaacabbbda
*/