#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = (1 << 17) + 5;
const LL MOD = 998244353;
const LL inv2 = (MOD + 1) / 2;

int n;
LL a[N], b[N];
void fwt(LL *arr, int lim, const LL coe[2][2]) {
	for(int i = 1; i < lim; i <<= 1)
		for(int j = 0; j < lim; j += (i << 1))
			for(int k = 0; k < i; k++) {
				LL x = arr[j + k], y = arr[j + i + k];
				arr[j + k] = (coe[0][0] * x % MOD + coe[0][1] * y % MOD) % MOD;
				arr[j + i + k] = (coe[1][0] * x % MOD + coe[1][1] * y % MOD) % MOD;
			}
}

LL x[N], y[N], z[N];

int main() {
	scanf("%d", &n);
	n = 1 << n;
	for(int i = 0; i < n; i++) scanf("%lld", &a[i]);
	for(int i = 0; i < n; i++) scanf("%lld", &b[i]);
	// or
	for(int i = 0; i < n; i++) x[i] = a[i], y[i] = b[i];
	const LL coe_or[2][2] = {{1, 0}, {1, 1}};
	fwt(x, n, coe_or), fwt(y, n, coe_or);
	for(int i = 0; i < n; i++) z[i] = x[i] * y[i] % MOD;
	const LL icoe_or[2][2] = {{1, 0}, {MOD - 1, 1}};
	fwt(z, n, icoe_or);
	for(int i = 0; i < n; i++) printf("%lld ", z[i]);
	puts("");
	// and
	for(int i = 0; i < n; i++) x[i] = a[i], y[i] = b[i];
	const LL coe_and[2][2] = {{1, 1}, {0, 1}};
	fwt(x, n, coe_and), fwt(y, n, coe_and);
	for(int i = 0; i < n; i++) z[i] = x[i] * y[i] % MOD;
	const LL icoe_and[2][2] = {{1, MOD - 1}, {0, 1}};
	fwt(z, n, icoe_and);
	for(int i = 0; i < n; i++) printf("%lld ", z[i]);
	puts("");
	// xor
	for(int i = 0; i < n; i++) x[i] = a[i], y[i] = b[i];
	const LL coe_xor[2][2] = {{1, 1}, {1, MOD - 1}};
	fwt(x, n, coe_xor), fwt(y, n, coe_xor);
	for(int i = 0; i < n; i++) z[i] = x[i] * y[i] % MOD;
	const LL icoe_xor[2][2] = {{inv2, inv2}, {inv2, MOD - inv2}};
	fwt(z, n, icoe_xor);
	for(int i = 0; i < n; i++) printf("%lld ", z[i]);
	puts("");
	return 0;
}