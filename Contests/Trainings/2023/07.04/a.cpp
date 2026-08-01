#include <bits/stdc++.h>

typedef long long LL;

LL mod;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL inv(LL x) { return qpow(x, mod - 2); }

int main() {
	int T;
	scanf("%lld%d", &mod, &T);
	while(T--) {
		LL a1, b1, a2, b2;
		scanf("%lld%lld%lld%lld", &a1, &b1, &a2, &b2);
		if((a1 + b1) % mod != (a2 + b2) % mod) { puts("-1"); continue; }
		LL a = a1, target = a2, s = (a1 + b1) % mod;
		LL invs = inv(s);
		int ans = 0, within = 1;
		for(int i = 0; i <= 31; i++) {
			LL k = (a - target + mod) % mod * invs % mod;
			if(k < within) { ans = i; break; }
			within *= 2, a *= 2;
		}
		printf("%d\n", ans);
	}
	return 0;
}