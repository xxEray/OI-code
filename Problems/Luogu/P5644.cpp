#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

typedef long long LL;

const int N = 1e5 + 5;
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

int n;
int a[N];
std::vector<LL> b[N << 2];

LL tx[N * 4], ty[N * 4], tz[N * 4];

void cdq(int x, int l, int r) {
	if(l == r) {
		b[x].resize(a[l] + 1);
		b[x][0] = 1;
		b[x][a[l]] = MOD - 1;
		return;
	}
	int mid = (l + r) >> 1;
	cdq(x << 1, l, mid), cdq(x << 1 | 1, mid + 1, r);
	int l1 = b[x << 1].size(), l2 = b[x << 1 | 1].size();
	l1--, l2--;
	int len = l1 + l2;
	for(int i = 0; i <= len; i++) tx[i] = ty[i] = 0;
	for(int i = 0; i <= l1; i++) tx[i] = b[x << 1][i];
	for(int i = 0; i <= l2; i++) ty[i] = b[x << 1 | 1][i];
	mul(tx, ty, tz, len);
	b[x].resize(len + 1);
	for(int i = 0; i <= len; i++) b[x][i] = tz[i];
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	cdq(1, 2, n);
	LL ans = 0;
	// for(int i = 0; i < (int)b[1].size(); i++) if(b[1][i]) printf("[%d] %lld\n", i, b[1][i]);
	for(int i = 1; i < (int)b[1].size(); i++) (ans += b[1][i] * inv(i + a[1]) % MOD) %= MOD;
	printf("%lld\n", (ans * a[1] % MOD + 1) % MOD);
	return 0;
}