#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

int n;
int a[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		std::sort(a + 1, a + n + 1);
		LL ans = 0, last = 0;
		for(int i = 1; i <= n; i++)
			if(a[i] <= last + 1) last = a[i];
			else ans += a[i] - (last + 1), last = last + 1;
		printf("%lld\n", ans);
	}
	return 0;
}