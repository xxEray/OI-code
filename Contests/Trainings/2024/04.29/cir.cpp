#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

LL n, A;

std::vector<int> prime;
bool isprm[N];
int mu[N];
void sieve() {
	for(int i = 2; i <= 1000000; i++) isprm[i] = true;
	mu[1] = 1;
	for(int i = 2; i <= 1000000; i++) {
		if(isprm[i]) prime.emplace_back(i), mu[i] = -1;
		for(int p : prime) {
			if((LL)p * i > 1000000) break;
			isprm[p * i] = false;
			if(i % p == 0) {
				mu[p * i] = 0;
				break;
			} else mu[p * i] = -mu[i];
		}
	}
}

int main() {
#ifndef DEBUG
	freopen("cir.in", "r", stdin);
	freopen("cir.out", "w", stdout);
#endif
	sieve();
	scanf("%lld%lld", &n, &A);
	n = std::min(n, 1000000LL);
	LL ans = 0;
	for(LL d = 1; d < n; d++) {
		LL bd = (A * d > 1000000 ? 0LL : (999999999999LL / ((A * d) * (A * d))));
		LL ret = -1;
		for(LL i = 0; i * i <= bd && i * d < n; i++) ret += std::min((LL)(sqrt(bd - i * i) + 1e-8), (n - 1) / d) + 1;
		ans += mu[d] * ret;
		// printf("d = %lld, bd = %lld, ret = %lld, mu = %d\n", d, bd, ret, mu[d]);
	}
	printf("%lld\n", ans);
	return 0;
}