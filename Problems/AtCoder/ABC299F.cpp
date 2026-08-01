#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 100 + 5;
const LL MOD = 998244353;

int n;
char s[N];
int nxt[N][30], last[30];

LL f[N][N];
LL solve(int x, int y) {
	for(int i = 0; i <= n + 1; i++) for(int j = 0; j <= n + 1; j++) f[i][j] = 0;
	f[x][y] = 1;
	for(int i = x; i < y; i++)
		for(int j = y; j <= n; j++) if(s[i] == s[j])
			for(int c = 0; c < 26; c++)
				(f[nxt[i][c]][nxt[j][c]] += f[i][j]) %= MOD;
	LL ret = 0;
	for(int i = y - 1; i >= 1; i--) {
		for(int j = y; j <= n; j++)
			(ret += f[i][j]) %= MOD;
		if(s[i] == s[x]) break;
	}
	// printf("solve(%d, %d) = %lld\n", x, y, ret);
	return ret;
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++) s[i] -= 'a';
	for(int i = n; i >= 0; i--) {
		for(int c = 0; c < 26; c++)
			nxt[i][c] = last[c];
		last[s[i]] = i;
	}
	LL ans = 0;
	for(int c = 0; c < 26; c++)
		for(int j = nxt[nxt[0][c]][c]; j && j <= n; j = nxt[j][c])
			(ans += solve(nxt[0][c], j)) %= MOD;
	printf("%lld\n", ans);
	return 0;
}