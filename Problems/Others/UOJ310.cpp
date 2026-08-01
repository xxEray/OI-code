#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 998244353;
const LL inv2 = (MOD + 1) / 2;

int n;
int a[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

void fwt(LL *arr, int lim, const LL coe[2][2]) {
	for(int i = 1; i < lim; i <<= 1)
		for(int j = 0; j < lim; j += (i << 1))
			for(int k = 0; k < i; k++) {
				LL x = arr[j + k], y = arr[j + i + k];
				arr[j + k] = (coe[0][0] * x % MOD + coe[0][1] * y % MOD) % MOD;
				arr[j + i + k] = (coe[1][0] * x % MOD + coe[1][1] * y % MOD) % MOD;
			}
}

LL x[N * 2];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int lim = (1 << 20);
	for(int i = 1; i <= n; i++) x[a[i]]++;
	const LL coe[2][2] = {{1, 1}, {1, MOD - 1}};
	fwt(x, lim, coe);
	for(int i = 0; i < lim; i++) x[i] = x[i] <= n ? x[i] : x[i] - MOD;
	// for(int i = 0; i < lim; i++) printf("%lld ", x[i]);
	// puts("");
	for(int i = 0; i < lim; i++) {
		// x[i] = o - j, n = o + j  ==>  o = (x[i] + n) / 2, j = (n - x[i]) / 2
		LL y = x[i];
		x[i] = qpow(MOD - 1, (n - y) / 2) * qpow(3, (n + y) / 2) % MOD;
	}
	const LL icoe[2][2] = {{inv2, inv2}, {inv2, MOD - inv2}};
	fwt(x, lim, icoe);
	printf("%lld\n", (x[0] + MOD - 1) % MOD);
	return 0;
}