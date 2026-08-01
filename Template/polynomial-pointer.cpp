#include <algorithm>
#include <cassert>

typedef long long LL;

const int N = /* maxcount */ + 5;
const LL MOD = 998244353;
const LL G_MOD = 3;
const LL INV_G_MOD = (MOD + 1) / G_MOD;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

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
inline void mul(LL *const x, LL *const y, LL *z, int len) { mul(x, y, z, len, len); }
void inv(LL *x, int len) {
	static LL y[N * 4], z[N * 4];
	for(int i = len + 1; i <= (len + 1) * 4; i++) x[i] = 0;
	for(int i = 0; i <= (len + 1) * 4; i++) y[i] = 0;
	y[0] = inv(x[0]);
	for(int i = 2; i <= (len + 1) * 2; i <<= 1) {
		mul(y, y, z, i - 1), mul(z, x, z, i - 1);
		for(int j = 0; j <= i - 1; j++) y[j] = (2 * y[j] - z[j] + MOD) % MOD;
	}
	for(int i = len + 1; i <= (len + 1) * 4; i++) y[i] = 0;
	for(int i = 0; i <= (len + 1) * 4; i++) x[i] = y[i];
}
void derivate(LL *x, int len) {
	for(int i = len + 1; i <= (len + 1) * 4; i++) x[i] = 0;
	for(int i = 1; i <= len; i++) x[i - 1] = x[i] * i % MOD;
	x[len] = 0;
}
void integrate(LL *x, int len) {
	for(int i = len + 1; i <= (len + 1) * 4; i++) x[i] = 0;
	for(int i = len + 1; i >= 1; i--) x[i] = x[i - 1] * inv(i) % MOD;
	x[0] = 0;
}
void ln(LL *x, int len) {
	static LL y[N * 4];
	assert(x[0] == 1);
	for(int i = 0; i <= len; i++) y[i] = x[i];
	for(int i = len + 1; i <= (len + 1) * 4; i++) x[i] = y[i] = 0;
	derivate(x, len), inv(y, len);
	mul(x, y, x, len - 1);
	integrate(x, len - 1);
	for(int i = len + 1; i <= (len + 1) * 4; i++) x[i] = 0;
}
void exp(LL *x, int len) {
	static LL y[N * 4], z[N * 4];
	assert(x[0] == 0);
	for(int i = len + 1; i <= (len + 1) * 4; i++) x[i] = 0;
	for(int i = 0; i <= (len + 1) * 4; i++) y[i] = z[i] = 0;
	x[0] = y[0] = 1;
	for(int i = 2; i <= (len + 1) * 2; i <<= 1) {
		for(int j = 0; j <= i * 4; j++) z[j] = y[j];
		ln(z, i - 1);
		mul(y, z, z, i - 1), mul(y, x, y, i - 1);
		for(int j = 0; j <= i - 1; j++) y[j] = (y[j] - z[j] + MOD) % MOD;
	}
	for(int i = len + 1; i <= (len + 1) * 4; i++) y[i] = 0;
	for(int i = 0; i <= (len + 1) * 4; i++) x[i] = y[i];
}