#include <bits/stdc++.h>

typedef long long LL;

const int N = 500 + 5;

int n;
int a[N];

int buftin[60000005], *const tin = buftin + 30000003;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), a[i] += a[i - 1];
	LL ans = 0;
	for(int i = 0; i <= n; i++) {
		for(int j = 1; j <= n; j++) for(int k = 0; k < j; k++) ans += tin[-(a[j] - a[k] + a[i])];
		for(int j = 1; j <= n; j++) for(int k = 0; k < j; k++) tin[a[j] - a[k] - a[i]]++;
	}
	// printf("ans = %lld\n", ans);
	memset(buftin, 0, sizeof(buftin));
	for(int i = 0; i <= n; i++) {
		for(int j = 1; j <= n; j++) for(int k = 0; k < j; k++)
			if(std::abs(2 * (a[j] - a[k]) + a[i]) <= 30000000) ans -= 3 * tin[-(2 * (a[j] - a[k]) + a[i])];
		tin[-a[i]]++;
	}
	// printf("ans = %lld\n", ans);
	for(int i = 1; i <= n; i++) for(int j = 0; j < i; j++) if(a[i] - a[j] == 0) ans += 2;
	// printf("ans = %lld\n", ans);
	assert(ans % 6 == 0);
	printf("%lld\n", ans / 6);
	return 0;
} /*
3
7 -4 -3
*/