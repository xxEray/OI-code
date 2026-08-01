#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;
const LL G_MOD = 3;
const LL INV_G_MOD = (MOD + 1) / G_MOD;

LL n, m, D;

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

struct Polynomial { LL w[N * 4]; int len; } a;
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

Polynomial f, g, x, y;

int main() {
	scanf("%lld%lld%lld", &D, &n, &m);
	if(D <= n - 2 * m) { printf("%lld\n", qpow(D, n)); return 0; }
	else if(n - 2 * m < 0) { puts("0"); return 0; }
	get_factorial(D);
	x.len = y.len = D;
	for(int i = 0; i <= D; i++) x.w[i] = invfac[i] * qpow(MOD - 1, i) % MOD * qpow((D - 2 * i + 2 * MOD) % MOD, n) % MOD;
	for(int i = 0; i <= D; i++) y.w[i] = invfac[i];
	f = mul(x, y, D);
	for(int i = 0; i <= D; i++) (f.w[i] *= C(D, i) * qpow(inv(2), i) % MOD * fac[i] % MOD) %= MOD;
	// for(int i = 0; i <= n; i++) printf("%lld ", f.w[i]);
	// puts("");
	for(int i = -D; i <= 0; i++) x.w[i + D] = qpow(MOD - 1, -i) * invfac[-i] % MOD;
	for(int i = 0; i <= D; i++) y.w[i] = fac[i] * f.w[i] % MOD;
	g = mul(x, y);
	for(int i = 0; i <= D; i++) (g.w[i + D] *= invfac[i]) %= MOD;
	LL ans = 0;
	for(int i = 0; i <= std::min(D, n - 2 * m); i++) (ans += g.w[i + D]) %= MOD;
	printf("%lld\n", ans);
	return 0;
}