#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, m;
char s[N], t[N];

int p[N];

int main() {
	scanf("%s%s", s + 1, t + 1);
	n = strlen(s + 1), m = strlen(t + 1);
	for(int j = 1, i = 1; j <= m; j++) {
		while(i <= n && s[i] != t[j]) i++;
		if(i > n) { puts("NO"); return 0; }
		p[j] = i;
		i++;
	}
	for(int j = m, i = n; i >= 1; j--) {
		while(i >= 1 && s[i] == s[i - 1]) i--;
		if(i <= 1) break;
		while(j >= 1 && p[j] > i) j--;
		if(j < 1) { puts("NO"); return 0; }
		p[j] = (s[i] == t[j] ? i : i - 1);
		i = p[j] - 1;
	}
	puts("YES");
	for(int i = 1; i <= m; i++) printf("%d ", p[i]);
	puts("");
	return 0;
}