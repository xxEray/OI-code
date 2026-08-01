#include <cstdio>
#include <algorithm>
#include <map>

typedef long long LL;

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }

int main() {
	LL l, r;
	scanf("%lld%lld", &l, &r);
	for(LL t = 0; ; t++)
		for(LL i = l; i <= l + t; i++)
			if(gcd(i, i + (r - l - t)) == 1)
				{ printf("%lld\n", r - l - t); return 0; }
	return 0;
}