#include <bits/stdc++.h>

const int N = 2000 + 5;

int n;
char s[N], t1[N], t2[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%s", &n, s + 1);
		bool ans = false;
		for(int i = 2; i <= n; i++) {
			strncpy(t1, s + 1, i - 1), t1[i - 1] = 0;
			strncpy(t2, s + i, n - i + 1), t2[n - i + 1] = 0;
			// printf("t1 = %s, t2 = %s\n", t1, t2);
			if(strcmp(t1, t2) < 0) ans = true;
		}
		puts(ans ? "Yes" : "No");
	}
	return 0;
}