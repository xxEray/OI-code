#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>

typedef long long LL;

const int N = 50 + 5;

int n, len;
LL K;
char s[N];

int m;
char t[N];

bool is_lyndon() {
	
}

int nxt[N];
void kmp(int u) {
	memset(nxt, 0, sizeof(nxt));
	for(int i = 1, j = 0; i <= n; i++) {
		while(j && t[j + 1] != t[i + 1]) j = nxt[j];
		if(t[j + 1] == t[i + 1]) j++;
		nxt[i] = j;
	}
}
int trans[N][300];
LL f[N][N], sum[N];
LL solve() {
	// build kmp automaton
	for(int i = 0; i <= m; i++) for(int c = 'a'; c <= 'z'; c++) trans[i][c] = 0;
	for(int i = 1; i <= m; i++) for(int c = t[i]; c <= 'z'; c++)
		if(t[i] == c) trans[i - 1][c] = i;
		else trans[i - 1][c] = trans[nxt[i - 1]][c];
	for(int c = 'a'; c <= 'z'; c++) trans[m][c] = trans[nxt[m]][c];
	// perform dp
	// f[i][j]
	memset(f, 0, sizeof(f)), memset(sum, 0, sizeof(sum));
	f[m][m] = 1;
	for(int i = m; i < n; i++) for(int j = 0; j <= m; j++)
		for(int c = (j == m ? 'a' : t[j + 1]); c <= 'z'; c++)
			f[i + 1][trans[j][c]] += f[i][j];
	// calculate the answer
	LL ret = 0;
	for(int i = m; i <= n; i++) for(int j = 0; j <= m; j++) sum[i] += f[i][j];
	printf("t = ");
	for(int i = 1; i <= m; i++) putchar(t[i]);
	printf(", ret = %lld\n", ret);
	return ret;
}

int main() {
	scanf("%d%lld%s", &n, &K, s + 1);
	len = strlen(s + 1);
	LL rnk = 0;
	for(int i = 1; i <= len; i++) {
		for(char j = 'a'; j < s[i]; j++) t[i] = j, m = i, rnk += solve();
		t[i] = s[i];
	}
	rnk++;
	rnk += K - 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 'a'; j <= 'z'; j++) {
			t[i] = j, m = i;
			LL tot = solve();
			if(rnk <= tot) break;
			rnk -= tot;
		}
		rnk -= is_lyndon();
		if(!rnk) break;
	}
	if(rnk) puts("-1");
	else {
		for(int i = 1; i <= m; i++) putchar(t[i]);
		puts("");
	}
	return 0;
}