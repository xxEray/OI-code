#include <cstdio>
#include <algorithm>
#include <cassert>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 998244353;
const LL G_MOD = 3;
const LL INV_G_MOD = (MOD + 1) / G_MOD;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int rev[N * 4];
void NTT(LL *arr, int lim, int type) {
	for(int i = 0; i < lim; i++) if(i < rev[i]) std::swap(arr[i], arr[rev[i]]);
	for(int i = 1; i < lim; i <<= 1) {
		LL wn = qpow(type == 1 ? G_MOD : INV_G_MOD, (MOD - 1) / (i << 1));
		for(int j = 0; j < lim; j += (i << 1)) {
			LL w = 1;
			for(int k = 0; k < i; k++, w = w * wn % MOD) {
				LL x = arr[j + k], y = w * arr[j + i + k] % MOD;
				arr[j + k] = (x + y) % MOD;
				arr[j + i + k] = (x - y + MOD) % MOD;
			}
		}
	}
	LL invlim = inv(lim);
	if(type == -1) for(int i = 0; i < lim; i++) arr[i] = arr[i] * invlim % MOD;
}
void mul(LL *const x_, LL *const y_, LL *z, int len, int lres) {
	static LL x[N * 4], y[N * 4];
	int lim = 1, w = 0;
	while(lim <= 2 * len + 2) lim <<= 1, w++;
	for(int i = 0; i <= len; i++) x[i] = x_[i], y[i] = y_[i];
	for(int i = len + 1; i < lim; i++) x[i] = y[i] = z[i] = 0;
	for(int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (w - 1));
	NTT(x, lim, 1), NTT(y, lim, 1);
	for(int i = 0; i < lim; i++) z[i] = x[i] * y[i] % MOD;
	NTT(z, lim, -1);
	for(int i = lres + 1; i <= 2 * len; i++) z[i] = 0;
}

LL a[N * 4], b[N * 4];

int main() {
	get_factorial(1e6);
	for(int i = 2; i <= 1000000; i++) a[i] = invfac[i - 2] * invfac[i] % MOD;
	for(int i = 1; i <= 1000000; i++) b[i] = invfac[i - 1] * invfac[i] % MOD * (i + 1) % MOD;
	mul(a, b, a, 1000000, 1000000);
	int T; scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		if(n == 2) puts("1");
		else printf("%lld\n", a[n] * fac[n - 3] % MOD * fac[n] % MOD);
	}
	return 0;
}