#include <bits/stdc++.h>

const int N = 10 + 5;

int n;
int a[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int _ = 1; _ <= n; _++) for(int i = n - 1; i >= 2; i--) if(a[i] > a[i + 1] && a[i - 1] < a[i]) std::swap(a[i], a[i + 1]);
		puts(std::is_sorted(a + 1, a + n + 1) ? "YES" : "NO");
	}
	return 0;
} /*
1 5 2 4 3
*/