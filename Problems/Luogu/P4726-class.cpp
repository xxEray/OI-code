#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 998244353;
const LL G_MOD = 3;
const LL INV_G_MOD = (MOD + 1) / G_MOD;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

struct Polynomial {
	LL w[N * 8];
	int len;
	Polynomial() : len(0) { memset(w, 0, sizeof(w)); }
};
int rev[N * 8];
inline LL mod(const LL &x) { return x >= MOD ? x - MOD : x; }
inline void NTT(LL *arr, int lim, int type) {
	for(int i = 0; i < lim; i++) if(i < rev[i]) std::swap(arr[i], arr[rev[i]]);
	for(int i = 1; i < lim; i <<= 1) {
		LL wn = qpow(type == 1 ? G_MOD : INV_G_MOD, (MOD - 1) / (i << 1));
		for(int j = 0; j < lim; j += (i << 1)) {
			LL w = 1;
			for(int k = 0; k < i; k++, w = w * wn % MOD) {
				LL x = arr[j + k], y = w * arr[j + i + k] % MOD;
				arr[j + k] = mod(x + y);
				arr[j + i + k] = mod(x - y + MOD);
			}
		}
	}
	LL invlim = inv(lim);
	if(type == -1) for(int i = 0; i < lim; i++) arr[i] = arr[i] * invlim % MOD;
}
inline Polynomial mul(Polynomial x, Polynomial y, int len) {
	int lim = 1, w = 0;
	for(int i = len + 1; i <= x.len; i++) x.w[i] = 0;
	for(int i = len + 1; i <= y.len; i++) y.w[i] = 0;
	x.len = y.len = len;
	while(lim <= 2 * len + 2) lim <<= 1, w++;
	for(int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (w - 1));
	NTT(x.w, lim, 1), NTT(y.w, lim, 1);
	for(int i = 0; i < lim; i++) x.w[i] = x.w[i] * y.w[i] % MOD;
	NTT(x.w, lim, -1);
	for(int i = len + 1; i <= x.len; i++) x.w[i] = 0;
	x.len = len;
	while(x.len > 0 && x.w[x.len] == 0) x.len--;
	return x;
}
inline  Polynomial mul(const Polynomial &x, const Polynomial &y) { return mul(x, y, std::max(x.len, y.len) * 2); }
inline Polynomial inv(Polynomial x, int len) {
	Polynomial y, z;
	y.w[0] = inv(x.w[0]);
	for(int i = 2; i <= (len + 1) * 2; i <<= 1) {
		y.len = i - 1;
		z = mul(y, y, y.len), z = mul(z, x, y.len);
		for(int j = 0; j <= y.len; j++) y.w[j] = (2 * y.w[j] - z.w[j] + MOD) % MOD;
	}
	for(int i = len + 1; i <= y.len; i++) y.w[i] = 0;
	y.len = len;
	while(y.len > 0 && y.w[y.len] == 0) y.len--;
	return y;
}
inline Polynomial inv(const Polynomial &x) { return inv(x, x.len); }
inline Polynomial derivate(Polynomial x) {
	for(int i = 1; i <= x.len; i++) x.w[i - 1] = x.w[i] * i % MOD;
	x.w[x.len] = 0;
	if(x.len) x.len--;
	return x;
}
inline Polynomial integrate(Polynomial x) {
	x.len++;
	for(int i = x.len; i >= 1; i--) x.w[i] = x.w[i - 1] * inv(i) % MOD;
	x.w[0] = 0;
	return x;
}
inline Polynomial ln(const Polynomial &x) { assert(x.w[0] == 1); return integrate(mul(derivate(x), inv(x), x.len)); }
inline Polynomial exp(Polynomial x, int len) {
	assert(x.w[0] == 0);
	Polynomial y, z;
	x.w[0] = y.w[0] = 1;
	for(int i = 2; i <= (len + 1) * 2; i <<= 1) {
		y.len = i - 1;
		z = mul(y, ln(y), y.len);
		y = mul(y, x, y.len);
		for(int j = 0; j <= y.len; j++) y.w[j] = (y.w[j] - z.w[j] + MOD) % MOD;
	}
	for(int i = len + 1; i <= y.len; i++) y.w[i] = 0;
	y.len = len;
	while(y.len > 0 && y.w[y.len] == 0) y.len--;
	return y;
}
inline Polynomial exp(const Polynomial &x) { return exp(x, x.len); }

Polynomial x;

int main() {
	int n;
	scanf("%d", &n);
	x.len = n - 1;
	for(int i = 0; i < n; i++) scanf("%lld", &x.w[i]);
	x = exp(x);
	for(int i = 0; i < n; i++) printf("%lld ", x.w[i]);
	return 0;
}
