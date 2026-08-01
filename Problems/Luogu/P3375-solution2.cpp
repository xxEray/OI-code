#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n, m;
char s[N], t[N];

int nxt[N];

int main() {
	scanf("%s%s", s + 1, t + 1);
	n = strlen(s + 1), m = strlen(t + 1);
	nxt[1] = 0;
	for(int i = 2, j = 0; i <= m; i++) {
		while(j && t[j + 1] != t[i]) j = nxt[j];
		if(t[j + 1] == t[i]) j++;
		nxt[i] = j;
	}
	for(int i = 1, j = 0; i <= n; i++) {
		while(j && t[j + 1] != s[i]) j = nxt[j];
		if(t[j + 1] == s[i]) j++;
		if(j == m) { printf("%d\n", i - j + 1); j = nxt[j]; }
	}
	for(int i = 1; i <= m; i++) printf("%d ", nxt[i]);
	return 0;
}