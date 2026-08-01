#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 1e9 + 7;

int n;
int a[N], b[N], c[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
		std::sort(a + 1, a + n + 1), std::sort(b + 1, b + n + 1);
		for(int i = 1, j = 0; i <= n; i++) {
			while(j < n && b[j + 1] < a[i]) j++;
			c[i] = j;
		}
		LL ans = 1;
		for(int i = 1; i <= n; i++) (ans *= c[i] - (i - 1)) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
}