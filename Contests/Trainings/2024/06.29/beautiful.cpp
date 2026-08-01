#include <bits/stdc++.h>

typedef long long LL;

const int V = 4e4;
const int N = V + 5;
const LL MOD = 998244353;

bool isprm[N];
int preprm[N];
std::vector<int> prime;
void sieve() {
	for(int i = 2; i <= V; i++) isprm[i] = true;
	prime.emplace_back(1);
	for(int i = 2; i <= V; i++) if(isprm[i]) {
		prime.emplace_back(i);
		for(int j = i + i; j <= V; j += i)
			isprm[j] = false;
	}
	for(int i = 1; i <= V; i++) preprm[i] = preprm[i - 1] + isprm[i];
}

int g[N * 2];
std::vector<int> vct;
int prime_count(int n) {
	vct.clear();
	auto hash = [&](int x) { return (LL)x * x <= n ? x : V + n / x; };
	for(int i = 1; i * i <= n; i++) vct.emplace_back(i), vct.emplace_back(n / i);
	std::sort(vct.begin(), vct.end());
	vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
	std::reverse(vct.begin(), vct.end());
	// printf("vct: "); for(int x : vct) printf("%d ", x); puts("");
	for(int i : vct) g[hash(i)] = i - 1;
	for(int k = 1; ; k++) {
		int p = prime[k];
		if((LL)p * p > n) break;
		for(int i : vct) {
			if(i < p * p) break;
			// printf("i = %d\n", i);
			g[hash(i)] -= g[hash(i / p)] - (k - 1);
		}
		// printf("k = %d (p=%d)\n", k, p);
		// for(int i = (int)vct.size() - 1; i >= 0; i--) printf("g[%d] = %d\n", vct[i], g[hash(vct[i])]);
	}
	return g[hash(n)];
}

int main() {
#ifndef DEBUG
	freopen("beautiful.in", "r", stdin);
	freopen("beautiful.out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	sieve();
	LL ans = 1;
	for(int p : prime) {
		if(p == 1) continue;
		if((LL)p * p > n) break;
		LL q = p;
		while((LL)q * p <= n) q *= p;
		if(q > n / 2) (ans *= 2) %= MOD;
	}
	int cnt = 1 + prime_count(n) - prime_count(n / 2);
	for(int i = 1; i <= cnt; i++) (ans *= i) %= MOD;
	printf("%lld\n", ans);
	return 0;
}