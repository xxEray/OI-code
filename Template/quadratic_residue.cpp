#include <random>
#include <utility>
#include <cassert>

typedef long long LL;

const int MOD = 998244353;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
int quadratic_residue(int n) {
	assert(n);
	std::mt19937 rnd(std::random_device{}());
	LL a = 0;
	while(true) {
		LL i = rnd() % MOD;
		if(qpow((i * i - n + MOD) % MOD, (MOD - 1) / 2) == MOD - 1) { a = i; break; }
	}
	LL w = (a * a - n + MOD) % MOD;
	using complex = std::pair<LL, LL>;
	auto mul = [&](complex x, complex y) { return complex((x.first * y.first + x.second * y.second % MOD * w) % MOD, (x.first * y.second + x.second * y.first) % MOD); };
	complex ret(1, 0), x(a, 1);
	int y = (MOD + 1) / 2;
	while(true) {
		if(y & 1) ret = mul(ret, x);
		if(!(y >>= 1)) break;
		x = mul(x, x);
	}
	return std::min(ret.first, MOD - ret.first);
}