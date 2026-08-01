#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e6 + 5;

int n;
LL a[N];

int main() {
#ifndef DEBUG
	freopen("num.in", "r", stdin);
	freopen("num.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	std::sort(a + 1, a + n + 1);
	LL sum = 0;
	int j = 0, ans = 0;
	for(int i = 1; i <= n; i++) {
		sum += a[i];
		while(j < n && a[j + 1] * i <= sum) j++;
		ans = std::max(ans, i - j);
	}
	printf("%d\n", ans);
	return 0;
}