#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

int n;
int p[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); p[x] = i; }
	int mn = n, mx = 1;
	LL ans = 0;
	for(int i = n; i >= 1; i--) {
		mn = std::min(mn, p[i]), mx = std::max(mx, p[i]);
		auto calc = [&](int L) {
			if(mx - mn + 1 > L || L > n) return;
			// printf("calc mn = %d, mx = %d, L = %d\n", mn, mx, L);
			ans += std::min(mn, n - L + 1) - std::max(mx - L + 1, 1) + 1;
		};
		calc(2 * n + 1 - 2 * i);
		if(i < n) calc(2 * n + 1 - i - (i + 1));
	}
	printf("%d %lld\n", 2 * n + 1, ans);
	return 0;
}