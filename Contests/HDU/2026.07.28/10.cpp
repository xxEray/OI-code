#include <bits/stdc++.h>

typedef long long LL;

const LL MOD = 998244353;

LL qpow(LL x, LL y) {
	LL ret = 1;
	for(; y; x = x * x % MOD, y >>= 1)
		if(y & 1) ret = ret * x % MOD;
	// printf("ret = %lld\n", ret);
	return ret;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		LL w, l;
		scanf("%lld%lld", &w, &l);
		printf("%lld\n", (qpow(w % MOD, l) + l - 1 + MOD) % MOD);
	}
	return 0;
}