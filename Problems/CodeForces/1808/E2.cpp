#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 100 + 5;

LL n;
int K;
LL mod;

LL f[N], g[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }

LL tmp[N];
void mul(LL *x, LL *const y) {
	for(int i = 0; i < K; i++) tmp[i] = 0;
	for(int i = 0; i < K; i++) for(int j = 0; j < K; j++) (tmp[(i + j) % K] += x[i] * y[j]) %= mod;
	for(int i = 0; i < K; i++) x[i] = tmp[i];
}
LL tmp2[N];
void qpow(LL *x, LL y) {
	for(int i = 0; i < K; i++) tmp2[i] = 0;
	tmp2[0] = 1;
	while(true) {
		// puts("114514");
		if(y & 1) mul(tmp2, x);
		if(!(y >>= 1)) break;
		mul(x, x);
	}
	for(int i = 0; i < K; i++) x[i] = tmp2[i];
}

int main() {
	scanf("%lld%d%lld", &n, &K, &mod);
	LL ans = qpow(K, n);
	// printf("ans = %lld\n", ans);
	for(int i = 0; i < K; i++) {
		for(int j = 0; j < K; j++) f[j] = 0, g[j] = (j * 2 % K == i ? 0 : 1);
		f[0] = 1;
		qpow(g, n), mul(f, g);
		(ans += mod - f[i]) %= mod; // , printf("sum = %d, substract = %lld\n", i, g[i]);
	}
	printf("%lld\n", ans);
	return 0;
}