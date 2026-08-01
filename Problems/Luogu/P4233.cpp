#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 998244353;
const LL G_MOD = 3;
const LL INV_G_MOD = (MOD + 1) / G_MOD;

int n;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL fac[N], invfac[N];
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

struct Polynomial { LL w[N * 12]; int len; } a;
int rev[N * 12];
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
Polynomial mul(Polynomial x, Polynomial y, int len) {
	int lim = 1, w = 0;
	for(int i = len + 1; i <= x.len; i++) x.w[i] = 0;
	for(int i = len + 1; i <= y.len; i++) y.w[i] = 0;
	x.len = y.len = len;
	while(lim <= (len + 1) * 2) lim <<= 1, w++;
	for(int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (w - 1));
	NTT(x.w, lim, 1), NTT(y.w, lim, 1);
	for(int i = 0; i < lim; i++) x.w[i] = x.w[i] * y.w[i] % MOD;
	NTT(x.w, lim, -1);
	while(x.len > 0 && x.w[x.len] == 0) x.len--;
	return x;
}
inline Polynomial mul(Polynomial x, Polynomial y) { return mul(x, y, std::max(x.len, y.len) * 2); }
Polynomial inv(Polynomial x, int len) {
	Polynomial y, z;
	y.w[0] = inv(x.w[0]);
	for(int i = 2; i <= (len + 1) * 2; i <<= 1) {
		y.len = i - 1;
		z = mul(y, y, y.len), z = mul(z, x, y.len);
		for(int j = 0; j <= y.len; j++) y.w[j] = (2 * y.w[j] - z.w[j] + MOD) % MOD;
	}
	while(y.len > 0 && y.w[y.len] == 0) y.len--;
	return y;
}
inline Polynomial inv(Polynomial x) { return inv(x, x.len); }

Polynomial f;

int main() {
	scanf("%d", &n);
	get_factorial(n);
	f.len = n;
	for(int i = 1; i <= n; i++) f.w[i] = qpow(2, (LL)i * (i - 1) / 2) * invfac[i] % MOD;
	f.w[0] = 1;
	f = inv(f);
	f.w[0] = (1 - f.w[0] + MOD) % MOD;
	for(int i = 1; i <= n; i++) f.w[i] = (MOD - f.w[i]) % MOD;
	puts("1");
	for(int i = 2; i <= n; i++) printf("%lld\n", f.w[i] ? qpow(2, (LL)i * (i - 1) / 2 - i) * fac[i - 1] % MOD * inv(f.w[i] * fac[i] % MOD) % MOD : -1LL);
	return 0;
}