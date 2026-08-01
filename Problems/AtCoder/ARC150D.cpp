#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

int n;
int p[N];

int dep[N];

LL h[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

int main() {
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) scanf("%d", &p[i]);
	for(int i = 1; i <= n; i++) h[i] = (h[i - 1] + inv(i)) % MOD;
	for(int i = 1; i <= n; i++) dep[i] = dep[p[i]] + 1;
	LL ans = 0;
	for(int i = 1; i <= n; i++) (ans += h[dep[i]]) %= MOD;
	printf("%lld\n", ans);
	return 0;
}