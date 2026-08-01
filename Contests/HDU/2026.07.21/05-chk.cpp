#include <bits/stdc++.h>

#define int long long

const int N = 1e5 + 5;

int n, m;
char s[N];

int fail[N];
int nxt[N][30];

signed main() {
	freopen("05.txt", "r", stdin);
	freopen("05-out.txt", "w", stdout);
	while(scanf("%lld%lld%s", &n, &m, s + 1) == 3) {
		long long k = 0;
		for(int i = 1; i < n; i++) {
			int t = fail[i - 1];
			while(t && s[t + 1] != s[i]) t = fail[t];
			if(i > 1 && s[t + 1] == s[i]) t++;
			fail[i] = t;
			// printf("fail[%lld] = %lld\n", i, fail[i]);
			printf("[%c]: k += ", s[i]);
			for(int c = 0; c < m; c++) {
				int j = i;
				int cn = 0;
				while(j && s[j + 1] - 'a' != c) j = fail[j], cn++;
				printf("%2lld ", cn);
				k += cn;
				if(s[j + 1] - 'a' == c) j++;
				nxt[i][c] = j;
			}
			puts("");
		}
		printf("k = %lld\n", k);
	}
	return 0;
}