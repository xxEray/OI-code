#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 1e9 + 7;
const LL inv2 = (MOD + 1) / 2;

int n, m;
LL a[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	LL sum = 0, suma = 0, sumb = 0;
	for(int i = 1; i <= n; i++) (suma += a[i] * (n - i + 1)) %= MOD;
	for(int i = 1; i <= n; i++) (sumb += a[i] * i) %= MOD;
	for(int i = 1; i <= n; i++) (sum += a[i]) %= MOD;
	LL t = (qpow(2, m) + MOD - 1) % MOD * qpow(2, m) % MOD * inv2 % MOD;
	t = t * n % MOD * sum % MOD;
	printf("%lld\n", std::max((t + qpow(2, m - 1) * suma % MOD + qpow(2, m - 1) * sumb % MOD) % MOD, (t + qpow(2, m) * suma % MOD) % MOD));
	return 0;
}