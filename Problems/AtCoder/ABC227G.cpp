#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 998244353;

std::vector<LL> prime;
bool isprm[N];

LL n, m;
LL t[N], cnt[N];

void sieve() {
	for(LL i = 2; i <= 1000000; i++) isprm[i] = true;
	for(LL i = 2; i <= 1000000; i++)
		if(isprm[i]) {
			prime.push_back(i);
			for(LL j = i + i; j <= 1000000; j += i)
				isprm[j] = false;
		}
}

int main() {
	sieve();
	scanf("%lld%lld", &n, &m);
	for(LL i = 1; i <= m; i++) t[i] = i;
	for(LL p : prime)
		for(LL i = p; i <= m; i += p)
			while(t[i] % p == 0) cnt[p]--, t[i] /= p;
	LL bd = n - m + 1;
	for(LL i = 0; i < m; i++) t[i] = i + bd;
	for(LL p : prime)
		for(LL i = (bd + p - 1) / p * p; i <= n; i += p)
			while(t[i - bd] % p == 0) cnt[p]++, t[i - bd] /= p;
	LL ans = 1;
	for(LL i = 0; i <= n - bd; i++) if(t[i] != 1) (ans *= 2) %= MOD;//, printf("i = %d, (%d != 1), ans *= 2\n", i + bd, t[i]);
	for(LL p : prime) (ans *= cnt[p] + 1) %= MOD;
	printf("%lld\n", ans);
	return 0;
} /*
1000000000000 1000000
*/