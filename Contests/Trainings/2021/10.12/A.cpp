#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e7 + 5;
const LL MOD = 1e9 + 7;

int isprm[N], prime[N];
LL phi[N], power[N];
int n, m, c;

LL inv[N];

LL qpow(LL a, LL b) { LL ret = 1; while(true) { if(b & 1) ret = ret * a % MOD; if(!(b >>= 1)) return ret; a = a * a % MOD; } }

void sieve() {
	phi[1]=1;
	for(int i = 2; i <= n; i++) isprm[i] = true;
	for(int i = 2; i <= n; i++) {
		if(isprm[i]) prime[++c] = i, phi[i] = i - 1, power[i] = qpow(i, m);
		for(int j = 1; j <= c; j++) {
			int p = prime[j];
			if((LL)p * i > n) break;
			isprm[i * p] = false, power[i * p] = power[i] * power[p] % MOD;
			if(i % p == 0)  {
				phi[i * p] = phi[i] * p;
				break;
			} else phi[i * p] = phi[i] * (p - 1);
		}
	}
	inv[1] = 1;
	for(int i = 2; i <= n; i++) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
}

int main() {
	scanf("%d%d", &n, &m);
	sieve();
	LL ans = m;
	// for(int i = 1; i <= 100; i++) printf("%lld ", phi[i]); puts("");
	for(int i = 2; i <= n; i++) (ans += phi[i] * (power[i] + MOD - 1) % MOD * inv[i - 1] % MOD) %= MOD;
	printf("%lld\n", ans);
	return 0;
}