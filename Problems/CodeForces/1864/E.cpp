#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

int n;
int a[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

LL ans;
void calc(int k, int l, int r) {
	if(l > r || k < 0) return;
	// printf("k = %d, l = %d, r = %d\n", k, l, r);
	int base = (a[l] & ~((1 << k) - 1));
	int mid = std::lower_bound(a + l, a + r + 1, base | (1 << (k - 1))) - a;
	(ans += (LL)(mid - l) * (r - mid + 1) % MOD * (__builtin_popcount(base) + 1)) %= MOD;
	(ans += (LL)(mid - l) * (r - mid + 1) % MOD * (__builtin_popcount(base) + 2)) %= MOD;
	calc(k - 1, l, mid - 1), calc(k - 1, mid, r);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		std::sort(a + 1, a + n + 1);
		ans = 0;
		calc(30, 1, n);
		std::map<int, int> mp;
		for(int i = 1; i <= n; i++) mp[a[i]]++;
		for(auto &p : mp)
			(ans += (LL)p.second * p.second % MOD * (__builtin_popcount(p.first) + 1)) %= MOD;
		// printf("sum = %lld\n", ans);
		printf("%lld\n", ans * inv((LL)n * n % MOD) % MOD);
	}
	return 0;
} /*
1
2
2 3
*/