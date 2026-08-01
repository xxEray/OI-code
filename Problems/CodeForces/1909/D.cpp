#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n;
LL K;
LL a[N];

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%lld", &n, &K);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		bool same = true;
		for(int i = 2; i <= n; i++) same &= (a[i] == a[i - 1]);
		if(same) { puts("0"); continue; }
		int tin[3] = {};
		LL g = 0;
		for(int i = 1; i <= n; i++) {
			g = gcd(g, std::abs(a[i] - K));
			if(a[i] - K > 0) tin[1]++;
			else if(a[i] - K < 0) tin[0]++;
			else tin[2]++;
		}
		if(g == 0 || tin[2] || (tin[0] && tin[1])) { puts("-1"); continue; }
		LL ans = 0;
		for(int i = 1; i <= n; i++) ans += std::abs(a[i] - K) / g - 1;
		printf("%lld\n", ans);
	}
	return 0;
}