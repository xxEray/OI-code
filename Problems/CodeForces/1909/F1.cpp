#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

int n;
int a[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		LL ans = 1;
		for(int i = 1; i <= n; i++) {
			int delta = a[i] - a[i - 1];
			LL v = i - a[i - 1];
			if(delta == 0);
			else if(delta == 1) (ans *= 2 * v - 1) %= MOD;
			else if(delta == 2) (ans *= (v - 1) * (v - 1) % MOD) %= MOD;
			else ans = 0;
		}
		if(a[n] != n) ans = 0;
		printf("%lld\n", ans);
	}
	return 0;
}