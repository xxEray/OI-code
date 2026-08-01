#include <bits/stdc++.h>

typedef long long LL;

const int N = 4e6 + 5;
const LL MOD = 998244353;

LL n, m;

std::vector<int> prime;
bool isprm[N];
int mu[N];
void sieve(int mx) {
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	mu[1] = 1;
	for(int i = 2; i <= mx; i++) {
		if(isprm[i]) prime.emplace_back(i), mu[i] = -1;
		for(int p : prime) {
			if((long long)p * i > mx) break;
			isprm[p * i] = false;
			if(i % p == 0) {
				mu[i * p] = 0;
				break;
			} else mu[p * i] = -mu[i];
		}
	}
}

int main() {
	sieve(4e6);
	scanf("%lld%lld", &n, &m);
	LL ans = 0;
	int mn = sqrt(std::min(n, m));
	for(int i = 1; i <= mn; i++) (ans += (mu[i] + MOD) % MOD * ((n / ((LL)i * i)) % MOD) % MOD * ((m / ((LL)i * i)) % MOD)) %= MOD;
	printf("%lld\n", ans);
	return 0;
}