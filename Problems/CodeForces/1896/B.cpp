#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
char s[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%s", &n, s + 1);
		int l = 1, r = n;
		while(l <= n && s[l] == 'B') l++;
		while(r >= 1 && s[r] == 'A') r--;
		if(l > r) puts("0");
		else printf("%d\n", r - l);
	}
	return 0;
} /*
AABBBBAAAABBBAA
*/