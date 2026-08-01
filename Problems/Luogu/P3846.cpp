#include <bits/stdc++.h>

typedef long long LL;

LL p, b, n;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % p; if(!(y >>= 1)) return ret; x = x * x % p; } }

int main() {
	scanf("%lld%lld%lld", &p, &b, &n);
	LL sq = sqrt(p);
	std::map<LL, LL> mp;
	for(int i = 0; i <= sq; i++) mp[qpow(b, i * sq)] = i * sq;
	LL ans = 1e12;
	for(int i = 0; i <= sq; i++) {
		LL v = qpow(b, i);
		v = n * qpow(v, p - 2) % p;
		if(mp.count(v)) ans = std::min(ans, mp[v] + i);
	}
	if(ans == 1000000000000) puts("no solution");
	else printf("%lld\n", ans);
	return 0;
}