#include <cstdio>
#include <algorithm>

typedef long long LL;

LL n, s, k;

LL gcd(LL a, LL b) { return a % b ? gcd(b, a % b) : b; }

// ax + by = 1
LL exgcd(LL a, LL b, LL &x, LL &y) {
	if(b == 0) {
		x = 1, y = 0;
		return a;
	}
	LL g = exgcd(b, a % b, x, y);
	LL tmp = x;
	x = y;
	y = tmp - a / b * y;
	return g;
}

int main() {
	int T;
	std::scanf("%d", &T);
	while(T--) {
		std::scanf("%lld%lld%lld", &n, &s, &k);
		k %= n;
		s = (-s + n * ((s + n - 1) % n) + n) % n;
		LL g = gcd(s, gcd(k, n)); // gcd(s, k, n)
		n /= g, s /= g, k /= g;
		if(gcd(k, n) != 1) { std::printf("-1\n"); continue; }
		LL t, y;
		exgcd(k, n, t, y);
		t = (t + n * ((-t + n - 1) % n) + n) % n;
		std::printf("%lld\n", (t * s) % n);
	}
	return 0;
} /*
   s + tk ≡ 0 (mod n)
=> tk ≡ -s (mod n)
=> g = gcd(-s, k, n)
=> gcd(k, n) ≠ 1 -> quit
=> replace k' = k / g, s' = -s / g, n' = n / g
=> t = inv(k', mod n') * s'
=> t' = inv(k', mod n')
=> t' * k' ≡ 1 (mod n')
=> t'k' + yn' = 1
*/