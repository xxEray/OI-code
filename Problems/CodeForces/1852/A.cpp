#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n, K;
int a[N];

bool check(LL x) {
	for(int i = 1; i <= K && x >= 1; i++)
		x -= std::upper_bound(a + 1, a + n + 1, x) - a - 1;
	return x >= 1;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		std::sort(a + 1, a + n + 1);
		LL l = 1, r = 4.01e10;
		while(l < r) {
			LL mid = (l + r) >> 1;
			if(check(mid)) r = mid;
			else l = mid + 1;
		}
		printf("%lld\n", l);
	}
	return 0;
}