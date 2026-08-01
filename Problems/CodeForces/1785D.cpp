#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = (1 << 20) + 5;
const LL MOD = 998244353;
const LL G_MOD = 3;
const LL INV_G_MOD = (MOD + 1) / G_MOD;


LL fac[N], invfac[N];
LL qpow(LL x, LL y, LL mod = MOD) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL inv(LL x, LL mod = MOD) { return qpow(x, mod - 2, mod); }
LL C(int x, int y, LL mod = MOD) { return x < y ? 0 : fac[x] * invfac[y] % mod * invfac[x - y] % mod; }
void get_factorial(int mx, LL mod = MOD) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % mod;
	invfac[mx] = inv(fac[mx], mod);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % mod;
}

LL f[N], a[N], b[N];

int n;

int rev[N];
void init_NTT(int m) {
	// lim = (1 << m), w = m
	for(int i = 0; i < (1 << m); i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (m - 1));
}
void NTT(LL *arr, int type, int m) {
	for(int i = 0; i < (1 << m); i++) if(i < rev[i]) std::swap(arr[i], arr[rev[i]]);
	for(int i = 1; i < (1 << m); i <<= 1) {
		LL wn = qpow(type == 1 ? G_MOD : INV_G_MOD, (MOD - 1) / (i << 1));
		for(int j = 0; j < (1 << m); j += (i << 1)) {
			LL w = 1;
			for(int k = 0; k < i; k++, w = w * wn % MOD) {
				LL x = arr[j + k], y = w * arr[j + i + k] % MOD;
				arr[j + k] = (x + y) % MOD;
				arr[j + i + k] = (x - y + MOD) % MOD;
			}
		}
	}
	LL invlimit = inv(1 << m);
	if(type == -1) for(int i = 0; i < (1 << m); i++) (arr[i] *= invlimit) %= MOD;
}

inline LL fact(int x) { return x < 0 ? 0 : fac[x]; }
inline LL invfact(int x) { return x < 0 ? 0 : invfac[x]; }

int main() {
	get_factorial(1 << 20);
	scanf("%d", &n);
	f[0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < (1 << (i - 1)); j++) a[j] = f[j] * invfact(j) % MOD * invfact((1 << (i - 1)) - j - 1) % MOD;
		for(int j = 0; j < (1 << i); j++) b[j] = invfact(j - 1) * invfact((1 << (i - 1)) - j) % MOD;
		init_NTT(i);
		NTT(a, 1, i), NTT(b, 1, i);
		for(int j = 0; j < (1 << i); j++) (a[j] *= b[j]) %= MOD;
		NTT(a, -1, i);
		for(int j = 0; j < (1 << i); j++) f[j] = 2 * fact(j - 1) % MOD * fact((1 << i) - j - 1) % MOD * fact(1 << (i - 1)) % MOD * a[j] % MOD;
		// (f[i][j] += 2 * fac[1 << (i - 1)] % MOD * f[i - 1][k] % MOD * C(j - 1, k) % MOD * C((1 << i) - (j + 1), (1 << (i - 1)) - (k + 1)) % MOD) %= MOD;
	}
	for(int i = 0; i < (1 << n); i++) printf("%lld\n", f[i]);
	return 0;
}