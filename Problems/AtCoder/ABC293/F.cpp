#include <cstdio>
#include <algorithm>
#include <cmath>

typedef __int128_t LL;
const int D = 7;

LL n;

inline bool solve(int s, int mx) {
	LL l = 2, r = ceill(powl(n, (long double)1 / mx));
	while(l < r) {
		LL mid = (l + r) >> 1;
		LL ret = 0, power = 1;
		for(int i = 0; i <= mx; i++) ret += (s >> i & 1) * power, power *= mid;
		if(ret == n) { l = mid; break; }
		else if(ret < n) l = mid + 1;
		else r = mid - 1;
	}
	LL ret = 0, power = 1;
	for(int i = 0; i <= mx; i++) ret += (s >> i & 1) * power, power *= l;
	if(ret == n)
		{ /* printf("%lld ", (long long)l); */ return true; }
	return false;
}

LL power[100];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		long long n_;
		scanf("%lld", &n_);
		n = n_;
		LL ans = 1 + (n > 2); // n - 1, n
		// printf("%lld %lld ", (long long)n, (long long)(n - 1));
		for(int i = 2; i <= D; i++) for(int s = 0; s < (1 << i); s++) ans += solve(s | (1 << i), i);
		LL mx = floorl(powl(n, (long double)1 / (D + 1)));
		for(LL x = 2; x <= mx; x++) {
			int ub = ceill(logl(n) / logl(x));
			power[0] = 1;
			for(int i = 1; i <= ub; i++) power[i] = power[i - 1] * x;
			LL tmp = n;
			for(int i = ub; i >= 0; i--) if(power[i] <= tmp) tmp -= power[i];
			ans += (tmp == 0);
			// if(tmp == 0) printf("%lld ", (long long)x);
		}
		printf("%lld\n", (long long)ans);
	}
	return 0;
}