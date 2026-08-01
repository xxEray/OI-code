#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n, m;
LL a[N], b[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= m; i++) scanf("%lld", &b[i]);
	for(int j = 1; j <= m; j++) {
		LL lowest = 0;
		for(int i = 1; i <= n; i++) {
			LL v = std::max(std::min(a[i], b[j]) - lowest, 0LL);
			lowest = std::max(lowest, std::min(a[i], b[j]));
			a[i] += v;
			if(lowest == b[j]) break;
		}
	}
	for(int i = 1; i <= n; i++) printf("%lld\n", a[i]);
	return 0;
}