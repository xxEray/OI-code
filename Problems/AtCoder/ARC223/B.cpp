#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

int n, K;
int a[N];

LL qpow(LL x, LL y) {
	LL ret = 1;
	for(; y; (x *= x) %= MOD, y >>= 1) if(y & 1) (ret *= x) %= MOD;
	return ret;
}

LL fac[N], invfac[N];
void getfac(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = qpow(fac[mx], MOD - 2);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }

int main() {
	getfac(2e5);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		int last = -1, cntl = 0, cnt = 0;
		LL ans = 1;
		std::map<int, int> mp;
		for(int i = 1; i <= n; i++) {
			if(a[i] % K == last || K - a[i] % K == last) {
				cntl += (a[i] % K == last), cnt++;
				if(2 * last % K == 0) mp[a[i]]++;
			} else {
				if(last != -1) {
					if(2 * last % K) (ans *= C(cnt, cntl)) %= MOD;
					else {
						(ans *= fac[cnt]) %= MOD;
						for(const auto &[x, y] : mp) (ans *= invfac[y]) %= MOD;
					}
				}
				mp.clear();
				last = std::min(a[i] % K, K - a[i] % K);
				cnt = cntl = 0;
				cntl += (a[i] % K == last), cnt++;
				if(2 * last % K == 0) mp[a[i]]++;
			}
		}
		if(last != -1) {
			if(2 * last % K) (ans *= C(cnt, cntl)) %= MOD;
			else {
				(ans *= fac[cnt]) %= MOD;
				for(const auto &[x, y] : mp) (ans *= invfac[y]) %= MOD;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}