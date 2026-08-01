#include <bits/stdc++.h>

typedef long long LL;

LL n, m;

std::unordered_map<LL, LL> cnt;

int main() {
	scanf("%lld%lld", &n, &m);
	for(LL y = 2; y * y + y + 1 <= n; y++) {
		LL z = y * y + y + 1;
		auto calc = [&](LL x) -> void {
			if(x <= y) return;
			cnt[x]++;
		};
		for(LL i = 1; i * i <= z; i++) if(z % i == 0) {
			calc(i);
			if(i != z / i) calc(z / i);
		}
	}
	for(auto &[x, y] : cnt) printf("%lld %lld\n", x, y);
	if(m == 0) printf("%lld\n", n - (LL)cnt.size());
	else {
		LL ans = 0;
		for(auto &[x, y] : cnt) ans += (y == m);
		printf("%lld\n", ans);
	}
	return 0;
}