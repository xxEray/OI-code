#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 4e5 + 5;
const LL MOD = 998244353;

int n;

LL fac[N], invfac[N];
LL qpow(LL x, LL y, LL mod = MOD) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL inv(LL x, LL mod = MOD) { return qpow(x, mod - 2, mod); }
LL C(int x, int y, LL mod = MOD) { return fac[x] * invfac[y] % mod * invfac[x - y] % mod; }
void get_factorial(int mx, LL mod = MOD) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % mod;
	invfac[mx] = inv(fac[mx], mod);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % mod;
}


int main() {
	scanf("%d", &n);
	get_factorial(2 * n);
	printf("%lld\n", );
	return 0;
}