#include <cstdio>

typedef long long LL;
const LL MOD = 998244353;

int main() {
	LL a, b, c;
	std::scanf("%lld%lld%lld", &a, &b, &c);
	a = (1 + a) * a / 2 % MOD;
	b = (1 + b) * b / 2 % MOD;
	c = (1 + c) * c / 2 % MOD;
	std::printf("%lld\n", a * b % MOD * c % MOD);
	return 0;
}