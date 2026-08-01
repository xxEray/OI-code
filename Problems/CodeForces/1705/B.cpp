#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

LL a[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		int st = 1;
		while(st <= n && a[st] == 0) st++;
		LL ans = 0;
		for(int i = st; i < n; i++) ans += a[i] + (a[i] == 0);
		printf("%lld\n", ans);
	}
	return 0;
}