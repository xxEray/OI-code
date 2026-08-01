#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e5 + 5;

char s[N], t[N];
int n, m, Q;

int nxt[N];

int main() {
#ifndef DEBUG
	freopen("language.in", "r", stdin);
	freopen("language.out", "w", stdout); 
#endif
	scanf("%s%d", s + 1, &Q);
	n = strlen(s + 1);
	while(Q--) {
		scanf("%s", t + 1);
		m = strlen(t + 1);
		for(int i = 0; i <= m; i++) nxt[i] = 0;
		for(int i = 2, j = 0; i <= m; i++) {
			while(j && t[j + 1] != t[i]) j = nxt[j];
			if(t[j + 1] == t[i]) j++;
			nxt[i] = j;
		}
		int ans = 0;
		for(int i = 1, j = 0; i <= n; i++) {
			while(j && t[j + 1] != s[i]) j = nxt[j];
			if(t[j + 1] == s[i]) j++;
			if(j == m) ans++, j = 0;
		}
		printf("%d\n", ans);
	}
	return 0;
}
