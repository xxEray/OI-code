#include <bits/stdc++.h>

int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i += 2) printf("%d %d ", i + 1, i);
		puts("");
	}
	return 0;
}