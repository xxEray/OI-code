#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

typedef long long LL;

const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }

int main() {
	LL x, y;
	scanf("%lld%lld", &x, &y);
	LL ans = 0;
	LL v = std::abs(x - y);
	std::vector<LL> vct;
	for(LL i = 2; i * i <= v; i++) while(v % i == 0) vct.push_back(i), v /= i;
	if(v > 1) vct.push_back(v);
	std::sort(vct.begin(), vct.end());
	while(x && y && std::abs(x - y) > 1) {
		LL d = LLINF;
		for(LL p : vct) d = std::min(d, x - x / p * p);
		x -= d, y -= d, ans += d;
		LL g = gcd(x, y);
		x /= g, y /= g;
		x--, y--;
		ans++;
		for(auto it = vct.begin(); it != vct.end(); it++) if(*it == g) { vct.erase(it); break; }
	}
	if(x != y) ans += std::min(x, y);
	else ans++;
	printf("%lld\n", ans);
	return 0;
}