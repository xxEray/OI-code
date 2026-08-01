#include <cstdio>
#include <algorithm>
#include <map>

typedef long long LL;

const LL MOD = 998244353;

std::map<LL, LL> mp;
LL f(LL x) {
	if(x == 0) return 0;
	if(x == 1) return 1;
	if(mp[x]) return mp[x];
	if(x <= 20) return mp[x] = std::max(x, f(x / 2) * f((x + 1) / 2)) % MOD;
	else return mp[x] = f(x / 2) % MOD * (f((x + 1) / 2) % MOD) % MOD;
}

int main() {
	LL x;
	scanf("%lld", &x);
	printf("%lld\n", f(x));
	return 0;
}