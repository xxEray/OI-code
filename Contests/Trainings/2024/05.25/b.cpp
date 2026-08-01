#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;

int n;
int a[2 * N];

int main() {
#ifndef DEBUG
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = n + 1; i <= 2 * n; i++) a[i] = 1;
	for(int i = n; i >= 1; i--) {
		int cnt = 0;
		for(int j = i; j <= 2 * n; j += i) cnt += a[j];
		// assert(cnt >= 1);
		if(cnt == 1) {
			a[i] = 1;
			for(int j = i + i; j <= 2 * n; j += i) a[j] = 0;
		}
	}
	LL ans = 0;
	for(int i = 1; i <= 2 * n; i++) if(a[i]) ans += i;
	printf("%lld\n", ans);
	return 0;
}