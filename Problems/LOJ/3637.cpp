#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e7 + 5;
const LL MOD = 998244353;

int n, m, L, R, X;

int a[N];

inline LL sum(LL x, LL y) { return x > y ? 0 : (x + y) * (y - x + 1) / 2 % MOD; }

int main() {
	scanf("%d%d%d%d", &m, &L, &R, &X);
	for(int i = 0; i < m; i++) scanf("%1d", &a[i]), a[i] += X, n += a[i];
	LL ans = 0;
	if(L == 0) L++, (ans += (LL)n * (n - 1) / 2 + n) %= MOD;
	int len = 0;
	for(int i = 0; i < L; i++) len += a[i];
	LL pow233 = 1;
	for(int i = 1; i < L; i++) (pow233 *= 233) %= MOD;
	for(int k = L; k <= R; k++) {
		(pow233 *= 233) %= MOD;
		int c = len / k + 1, t = n - len;
		LL ret = 0;
		if(t < 2 * k - 2) (ret += sum(1, t / 2) * 2 % MOD + (t & 1) * (t / 2 + 1)) %= MOD;
		else {
			(ret += sum(1, k - 1) * 2) %= MOD;
			t -= 2 * k - 2;
			(ret += sum(k, k + t / c - 1) * c % MOD) %= MOD;
			(ret += (LL)(k + t / c) * (t % c)) %= MOD;
		}
		// printf("ret=%lld, ", ret);
		ret = (sum(1, n - k + 1) - ret + MOD) % MOD;
		// printf("k=%d, ans=%lld\n", k, ret);
		ans ^= pow233 * ret % MOD;
		len += a[k];
	}
	printf("%lld\n", ans);
	return 0;
}