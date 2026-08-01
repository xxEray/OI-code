#include <bits/stdc++.h>

typedef long long LL;

struct Barrett {
	LL p, m;
	void init() { m = ((__int128_t)1 << 64) / p; }
} mod;
LL operator%(LL x, const Barrett &y) { return x - ((__int128_t)x * y.m >> 64) * y.p; }
LL &operator%=(LL &x, const Barrett &y) { return x -= ((__int128_t)x * y.m >> 64) * y.p; }
// LL operator%(LL x, const Barrett &y) { return x % y.p; }
// LL &operator%=(LL &x, const Barrett &y) { return x %= y.p; }

bool isprm[105];
std::vector<int> prime;
void sieve() {
	for(int i = 2; i <= 100; i++) isprm[i] = true;
	for(int i = 2; i <= 100; i++) if(isprm[i]) {
		prime.emplace_back(i);
		for(int j = i + i; j <= 100; j += i) isprm[j] = false;
	}
}

std::unordered_map<LL, int> mp;
LL C[1005][1005], power2[(1 << 17) + 5], power3[1005];

void preprocess() {
	for(int i = 0; i <= 1000; i++) C[i][0] = 1;
	for(int i = 1; i <= 1000; i++) for(int j = 1; j <= i; j++) {
		C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		if(C[i][j] >= mod.p) C[i][j] -= mod.p;
	}
	power2[0] = 1;
	for(int i = 1; i <= (1 << 17); i++) {
		power2[i] = power2[i - 1] * 2;
		if(power2[i] >= mod.p) power2[i] -= mod.p;
	}
	power3[0] = 1;
	for(int i = 1; i <= 1000; i++) power3[i] = power3[i - 1] * 3 % mod;
}

std::vector<int> eponent;

LL dfs(int id, int sum, int cnt1, int prod) {
	// printf("dfs %d %d %d %d\n", id, sum, cnt1, prod);
	if(id == (int)eponent.size()) {
		if(sum & 1) return mod.p - power2[cnt1] * (power2[prod] - 1 + mod.p) % mod;
		else return power2[cnt1] * (power2[prod] - 1 + mod.p) % mod;
	}
	LL ret = 0;
	ret += dfs(id + 1, sum, cnt1, prod * (eponent[id] + 1));
	ret += dfs(id + 1, sum + 1, cnt1 + 1, prod * eponent[id]);
	ret += dfs(id + 1, sum + 2, cnt1, prod * (eponent[id] - 1));
	return ret % mod.p;
}

int main() {
#ifndef DEBUG
	freopen("pain.in", "r", stdin);
	freopen("pain.out", "w", stdout);
#endif
	int T; scanf("%d%lld", &T, &mod.p);
	sieve();
	preprocess();
	mod.init();
	while(T--) {
		LL n, n0;
		scanf("%lld", &n);
		if(mp.count(n)) { printf("%d\n", mp[n]); continue; }
		n0 = n;
		eponent.clear();
		int cnt1 = 0, cnt2 = 0;
		for(int p : prime) if(n % p == 0) {
			int cn = 0;
			while(n % p == 0) cn++, n /= p;
			if(cn == 1) cnt1++;
			else if(cn == 2) cnt2++;
			else eponent.emplace_back(cn);
		}
		// printf("cnt1 = %d, cnt2 = %d; ", cnt1, cnt2); for(int x : eponent) printf("%d ", x); puts("");
		LL ans = 0;
		for(int i = 0; i <= cnt1; i++)
			for(int j = 0; j <= cnt2; j++)
				for(int k = 0; k <= cnt2 - j; k++)
					(ans += C[cnt1][i] * C[cnt2][j] % mod * C[cnt2 - j][k] % mod * dfs(0, i + j, i + j, power2[cnt1 - i] * power3[cnt2 - j - k] * power2[j])) %= mod;
		ans = (ans + mod.p) % mod;
		mp[n0] = ans;
		printf("%lld\n", ans);
	}
	return 0;
} /*
4 998244353
6
60
25200
698377680
*/