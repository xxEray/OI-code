#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
int a[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		int ans = 0, x = n + 1, y = n + 1;
		for(int i = 1; i <= n; i++) {
			if(a[i] <= y) y = a[i];
			else if(a[i] <= x) x = a[i];
			else ans++, y = a[i];
			if(x < y) std::swap(x, y);
		}
		printf("%d\n", ans);
	}
	return 0;
}