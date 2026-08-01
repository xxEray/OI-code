#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e6 + 5;
const LL MOD = 998244353;

int n;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int p[N];
bool vis[N];
int cnt[N];
std::vector<int> factor[N];

int main() {
#ifndef DEBUG
	freopen("omphalos.in", "r", stdin);
	freopen("omphalos.out", "w", stdout);
#endif
	scanf("%d", &n);
	get_factorial(n);
	for(int i = 1; i <= n; i++) scanf("%d", &p[i]);
	for(int i = 1; i <= n; i++) if(!vis[i]) {
		int cn = 0;
		for(int j = i; !vis[j]; j = p[j]) cn++, vis[j] = true;
		cnt[cn]++;
	}
	// printf("cnt: "); for(int i = 1; i <= n; i++) printf("%d ", cnt[i]); puts("");
	for(int i = 1; i <= n; i++) if(cnt[i]) for(int j = i + i; j <= n; j += i) if(cnt[j]) factor[j].emplace_back(i);
	LL ans = 1;
	for(int i = 1; i <= n; i++) if(cnt[i]) {
		LL ret = 0;
		for(int j : factor[i]) ret += cnt[j] * j;
		if(!ret) {
			if(i == 1) (ans *= (cnt[i] == 1 ? 1LL : qpow(cnt[i], cnt[i] - 2)) * qpow(i, cnt[i] - 1) % MOD) %= MOD;
			else if(i == 2) (ans *= qpow(cnt[i], cnt[i] - 1) * qpow(i, cnt[i] - 1) % MOD) %= MOD;
			else ans = 0;
		} else {
			LL sum = 0;
			for(int j = 1; j <= cnt[i]; j++)
				(sum += qpow(ret, j) * C(cnt[i] - 1, j - 1) % MOD * qpow(cnt[i], cnt[i] - j) % MOD * qpow(i, cnt[i] - j)) %= MOD;
			(ans *= sum) %= MOD;
		}
		// printf("i = %d, ans = %lld\n", i, ans);
	}
	printf("%lld\n", ans);
	return 0;
} /*
15
1 3 2 5 6 7 4 9 10 11 12 13 14 15 8
*/