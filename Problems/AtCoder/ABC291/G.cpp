#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 5e5 + 5;
const LL MOD = 998244353;
const int INF = 0x3f3f3f3f;
const LL G_MOD = 3;
const LL INV_G_MOD = (MOD + 1) / G_MOD;

int n;
int a[N], b[N], e[N];
LL c[N * 4], d[N * 4];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

int rev[N * 4], limit;
void init(int mx) {
	limit = 1;
	int w = 0;
	while(limit <= mx) limit <<= 1, w++;
	for(int i = 0; i < limit; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (w - 1));
}
void NTT(LL *arr, int type) {
	for(int i = 0; i < limit; i++) if(i < rev[i]) std::swap(arr[i], arr[rev[i]]);
	for(int i = 1; i < limit; i <<= 1) {
		LL wn = qpow(type == 1 ? G_MOD : INV_G_MOD, (MOD - 1) / (i << 1));
		for(int j = 0; j < limit; j += (i << 1)) {
			LL w = 1;
			for(int k = 0; k < i; k++, w = w * wn % MOD) {
				LL x = arr[j + k], y = w * arr[j + i + k] % MOD;
				arr[j + k] = (x + y) % MOD;
				arr[j + i + k] = (x + MOD - y) % MOD;
			}
		}
	}
	LL invlim = inv(limit);
	if(type == -1) for(int i = 0; i < limit; i++) arr[i] = arr[i] * invlim % MOD;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	std::reverse(b + 1, b + n + 1);
	LL sum = 0;
	for(int i = 1; i <= n; i++) sum += a[i] + b[i];
	for(int j = 0; j < 5; j++) {
		for(int i = 0; i < limit; i++) c[i] = d[i] = 0;
		for(int i = 1; i <= n; i++) c[i] = a[i] >> j & 1, d[i] = d[i + n] = b[i] >> j & 1;
		init(2 * n);
		NTT(c, 1), NTT(d, 1);
		for(int i = 0; i < limit; i++) c[i] = c[i] * d[i] % MOD;
		NTT(c, -1);
		for(int i = n + 1; i <= 2 * n; i++) e[i - n] += c[i] << j;
	}
	int mn = INF;
	for(int i = 1; i <= n; i++) mn = std::min(mn, e[i]);
	printf("%lld\n", sum - mn);
	return 0;
}