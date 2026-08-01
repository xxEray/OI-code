#include <bits/stdc++.h>

typedef long long LL;

int main() {
	LL n, m;
	scanf("%lld%lld", &n, &m);
	LL ret = 1, base = 10 % (m * m);
	while(true) {
		if(n & 1) ret = ret * base % (m * m);
		if(!(n >>= 1)) break;
		base = base * base % (m * m);
	}
	printf("%lld\n", (ret / m) % m);
	return 0;
}