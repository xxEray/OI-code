#include <bits/stdc++.h>

typedef long long LL;

LL n;

std::map<LL, LL> mp;
LL f(LL x) {
	if(x < 2) return 0;
	if(mp.count(x)) return mp[x];
	return mp[x] = f(x / 2) + f((x + 1) / 2) + x;
}

int main() {
	scanf("%lld", &n);
	printf("%lld\n", f(n));
	return 0;
}