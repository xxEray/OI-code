#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 1e5 + 5;
const int MOD = 1019260817;

int n, Q, cipher;
int a[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

bool isprm[1000005];
std::vector<int> prime;
int factor[1000005];
void sieve(int mx) {
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	for(int i = 2; i <= mx; i++) {
		if(isprm[i]) prime.push_back(i);
		for(int p : prime) {
			if((LL)p * i > mx) break;
			isprm[i * p] = false;
			factor[i * p] = p;
			if(i % p == 0) break;
		}
	}
}

LL f(LL x) {
	if(x == 1) return 1;
	int p = factor[x];
	if(p == 0) p = x;
	int c = 0;
	while(x % p == 0) c++, x /= p;
	return f(x) * (c == 1 ? qpow(p, 114514) : qpow(p, 229028) * qpow(p + 1, 1919810LL * (c - 2) % (MOD - 1)) % MOD) % MOD;
}

int main() {
#ifndef DEBUG
	freopen("ai.in", "r", stdin);
	freopen("ai.out", "w", stdout);
#endif
	sieve(1e6);
	scanf("%d%d%d", &n, &Q, &cipher);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	LL lastans = 0;
	while(Q--) {
		int type, x, y;
		scanf("%d%d%d", &type, &x, &y);
		if(cipher) x ^= lastans, y ^= lastans;
		if(type == 1) a[x] = y;
		else {
			int prod = 1;
			for(int i = x; i <= y; i++) prod *= a[i];
			printf("%lld\n", (lastans = f(prod)));
		}
	}
	return 0;
}
