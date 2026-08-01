#include <bits/stdc++.h>

typedef long long LL;
const int N = 1e6 + 5;
const LL MOD = 1e9 + 7;

int n, Q;
LL a[N], b[N];
LL c[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

LL ts[N], tp[N];
LL edep[N];
LL sum[N];

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i < n; i++) scanf("%lld", &a[i]), (b[i] = b[i - 1] + a[i]) %= MOD;
	for(int i = 1; i <= n; i++) scanf("%lld", &c[i]);
	for(int i = 1; i <= n; i++) ts[i] = (ts[i - 1] + a[i] * c[i] % MOD * inv(b[i]) % MOD) % MOD;
	tp[0] = tp[1] = 1;
	for(int i = 2; i <= n; i++) tp[i] = tp[i - 1] * (2 * a[i] + b[i - 1]) % MOD * inv(b[i - 1]) % MOD;
	for(int i = 1; i <= n; i++)
		edep[i] = (c[1] + c[i] + 2 * (ts[i - 1] - ts[1] + MOD) % MOD) % MOD;
	for(int i = 1; i <= n; i++)
		sum[i] = (sum[i - 1] + 2 * edep[i] * a[i] % MOD * a[i] % MOD * inv(tp[i]) % MOD) % MOD;
	// for(int i = 1; i <= n; i++) printf("%lld ", edep[i]);
	// puts("");
	while(Q--) {
		int u, v;
		scanf("%d%d", &u, &v);
		if(u > v) std::swap(u, v);
		if(u == v) { puts("0"); continue; }
		printf("%lld\n", (edep[u] + edep[v] - sum[u - 1] * tp[u - 1] % MOD * inv(b[u - 1] * b[u] % MOD) % MOD - 2 * a[u] % MOD * inv(b[u]) % MOD * edep[u] % MOD + 2 * MOD) % MOD);
	}
	return 0;
} /*
10 10
385 177 198 757 514 457 442 201 319
768703242 888465093 249759279 288429103 629206115 111918639 152197940 27292714 8798037
*/