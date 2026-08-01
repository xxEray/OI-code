#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;
const LL inv3 = (MOD + 1) / 3;

int n;
char s[N];

LL f[N], g[N], h[N];
LL pre[N], pref[N];
LL vx[N * 4], vy[N * 4];

int limit;
LL invlimit;
int rv[20][N * 4];

inline LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
inline LL inv(LL x) { return qpow(x, MOD - 2); }

inline void NTT(LL *arr, int type, int *rev) {
	for(int i = 0; i < limit; i++) if(i < rev[i]) std::swap(arr[i], arr[rev[i]]);
	for(int i = 1; i < limit; i <<= 1) {
		LL wn = qpow(type == 1 ? 3 : inv3, (MOD - 1) / (i << 1));
		for(int j = 0; j < limit; j += (i << 1)) {
			LL w = 1;
			for(int k = 0; k < i; k++, w = w * wn % MOD) {
				LL x = arr[j + k], y = w * arr[j + i + k] % MOD;
				arr[j + k] = (x + y >= MOD ? x + y - MOD : x + y);
				arr[j + i + k] = (x - y < 0 ? x - y + MOD : x - y);
			}
		}
	}
	if(type == -1) for(int i = 0; i < limit; i++) (arr[i] *= invlimit) %= MOD;
}
inline void multiply(LL *x, LL *y, int len) {
	int w = 0;
	limit = 1;
	while(limit <= 2 * len + 2) limit <<= 1, w++;
	invlimit = inv(limit);
	NTT(x, 1, rv[w]), NTT(y, 1, rv[w]);
	for(int i = 0; i < limit; i++) (x[i] *= y[i]) %= MOD;
	NTT(x, -1, rv[w]);
}

void solve(int l, int r) {
	if(l == r) {
		// printf("f[%d] is originally -%lld\n", l, (MOD - f[l]) % MOD);
		if(l) (f[l] += MOD + pref[l - 1] * g[l] % MOD) %= MOD;
		pref[l] = ((l ? pref[l - 1] : 0) + f[l]) % MOD;
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	// f -= (f·g) * h
	for(int i = l; i <= mid; i++) vx[i - l] = f[i] * g[i] % MOD;
	for(int i = 0; i <= r - l; i++) vy[i] = h[i];
	multiply(vx, vy, r - l);
	for(int i = mid + 1; i <= r; i++) f[i] += MOD - vx[i - l], f[i] >= MOD ? f[i] -= MOD : 0;
	for(int i = 0; i < limit; i++) vx[i] = vy[i] = 0;
	solve(mid + 1, r);
}

int main() {
	scanf("%d%s", &n, s + 1);
	h[0] = 1;
	for(int i = 1; i <= n; i++) g[i] = (g[i - 1] * 10 + (s[i] - '0')) % MOD, h[i] = h[i - 1] * 10 % MOD;
	for(int w = 0; w <= 19; w++) for(int i = 0; i < (1 << w); i++) rv[w][i] = ((rv[w][i >> 1] >> 1) | ((i & 1) << (w - 1)));
	f[0] = 1;
	solve(0, n);
	// for(int i = 0; i <= n; i++) printf("f[%d] = %lld\n", i, f[i]);
	printf("%lld\n", f[n]);
	return 0;
}