#include <cstdio>
#include <algorithm>

typedef long long LL;

LL n, m;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld", &n, &m);
		LL now = 1, cnt = 0;
		while(now < n && now < m) now <<= 1, cnt++;
		if(now >= n) printf("%lld\n", cnt);
		else printf("%lld\n", cnt + (n - now + m - 1) / m);
	}
	return 0;
}