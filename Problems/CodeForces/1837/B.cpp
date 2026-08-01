#include <bits/stdc++.h>

const int N = 100 + 5;

int n;
char s[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%s", &n, s + 1);
		int ans = 0, now = 0;
		for(int i = 1; i <= n; i++) now = (s[i] == s[i - 1] ? now + 1 : 1), ans = std::max(ans, now);
		printf("%d\n", ans + 1);
	}
	return 0;
}