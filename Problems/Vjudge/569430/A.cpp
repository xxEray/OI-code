#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 1e9 + 7;

int n;
char s[N];

int nxt[N], sum[N], f[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		for(int i = 1; i <= n; i++) f[i] = 0;
		for(int j = 0, i = 2; i <= n; i++) {
			while(j && s[j + 1] != s[i]) j = nxt[j];
			if(s[j + 1] == s[i]) j++;
			nxt[i] = j;
		}
		for(int i = 1; i <= n; i++) sum[i] = sum[nxt[i]] + 1;
		for(int j = 0, i = 2; i <= n; i++) {
			while(j && s[j + 1] != s[i]) j = nxt[j];
			if(s[j + 1] == s[i]) j++;
			while(j > i / 2) j = nxt[j];
			f[i] = sum[j];
		}
		LL ans = 1;
		for(int i = 1; i <= n; i++) (ans *= f[i] + 1) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
}