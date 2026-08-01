#include <cstdio>
#include <algorithm>
#include <cassert>

typedef long long LL;
const int N = 3.6e5 + 5;
const LL MOD = 998244353;
const LL G_MOD = 3;
const LL INV_G_MOD = (MOD + 1) / G_MOD;

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

LL coe[N * 4];
LL f[N * 4], tmp[N * 4], buffer[25][N * 4];
int d;
void cdq(LL *x, int l, int r, int dep) {
	// printf("cdq [%d, %d] f=", l, r);
	// for(int i = 0; i <= 2 * (r - l + 1); i++) printf("%lld ", f[i]);
	// puts("");
	if(l == r) { x[l] = f[0]; return; }
	int mid = (l + r) >> 1;
	for(int i = 0; i <= 2 * (r - l + 1); i++) buffer[dep][i] = f[i];
	for(int i = 0; i <= 2 * (r - l + 1) - (r - mid); i++) f[i] = f[i + (r - mid)];
	for(int i = 2 * (r - l + 1) - (r - mid) + 1; i <= 2 * (r - l + 1); i++) f[i] = 0;
	cdq(x, l, mid, dep + 1);
	// f * coe^(mid - l + 1)
	for(int i = 0; i <= 2 * (r - l + 1); i++) f[i] = buffer[dep][i];
	for(int i = 0; i <= 2 * (r - l + 1); i++) tmp[i] = coe[i] * (mid - l + 1) % MOD;
	// exp(tmp, 2 * (r - l + 1));
	mul(f, tmp, f, 2 * (r - l + 1));
	for(int i = 0; i <= 2 * (r - l + 1) - 2 * (mid - l + 1); i++) f[i] = f[i + 2 * (mid - l + 1)];
	for(int i = 2 * (r - l + 1) - 2 * (mid - l + 1) + 1; i <= 2 * (r - l + 1); i++) f[i] = 0;
	cdq(x, mid + 1, r, dep + 1);
}
void solve(LL *x, int a, int n) {
	for(int i = 0; i <= 2 * d + 2; i++) f[i] = 0;
	int st = d + a, cnt = 0, num = -2;
	while(st <= 2 * d + 2) {
		f[st] = num == 2 || num == -2 ? 0 : (num + MOD) % MOD;
		cnt++;
		if(num == 2) num = 1, cnt = 0;
		else if(num == -2) num = -1, cnt = 0;
		else if(cnt == n) num = (num == -1 ? 2 : -2), cnt = 0;
		st++;
	}
	st = d + a, cnt = 0, num = 2;
	while(st >= 0) {
		f[st] = num == 2 || num == -2 ? 0 : (num + MOD) % MOD;
		cnt++;
		if(num == 2) num = 1, cnt = 0;
		else if(num == -2) num = -1, cnt = 0;
		else if(cnt == n) num = (num == -1 ? 2 : -2), cnt = 0;
		st--;
	}
	// printf("solve(%d, %d)\n", a, n);
	// printf("f: ");
	// for(int i = 0; i <= 2 * d + 2; i++) printf("%lld ", f[i]);
	// puts("");
	cdq(x, 0, d, 0);
	// printf("x: ");
	// for(int i = 0; i <= d; i++) printf("%lld ", x[i]);
	// puts("");
	for(int i = 0; i <= d; i++) (x[i] *= invfac[i]) %= MOD;
}

LL x[N * 4], y[N * 4], z[N * 4];

int main() {
	int a, b, c, n, m, K;
	scanf("%d%d%d%d%d%d%d", &d, &n, &m, &K, &a, &b, &c);
	get_factorial(2 * d);
	coe[0] = 1, coe[2] = 1;
	ln(coe, 2 * d + 2);
	solve(x, a, n), solve(y, b, m), solve(z, c, K);
	mul(x, y, x, d), mul(x, z, x, d);
	printf("%lld\n", x[d] * fac[d] % MOD);
	return 0;
}