#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 1e5 + 5;

LL n, m, mod;

LL fac[N], invfac[N];

void clear() {
	memset(fac, 0, sizeof(fac));
	memset(invfac, 0, sizeof(invfac));
}

LL qpow(LL a, LL b) { LL ret = 1; for(; b; b >>= 1) { if(b & 1) ret = ret * a % mod; a = a * a % mod; } return ret; }
void preprocess() {
	fac[0] = 1;
	for(int i = 1; i <= mod - 1; i++) fac[i] = fac[i - 1] * i % mod;
	invfac[mod - 1] = qpow(fac[mod - 1], mod - 2);
	for(int i = mod - 1; i >= 1; i--) invfac[i - 1] = invfac[i] * i % mod;
}
LL C(LL a, LL b) { return a <= mod && b <= mod ? fac[a] * invfac[b] % mod * invfac[a - b] % mod : C(a % mod, b % mod) * C(a / mod, b / mod) % mod; }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		clear();
		scanf("%lld%lld%lld", &n, &m, &mod);
		preprocess();
		printf("%lld\n", C(n + m, n));
	}
	return 0;
}