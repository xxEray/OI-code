#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;
const LL MOD = 998244353;

int n, K;
struct Node { int l, r; } a[N];

std::set<int> st;

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

struct BIT {
	LL t[N];
	void add(int x, LL v) { /* printf("add [%d] %d\n", x, v); */ while(x <= n) t[x] ^= v, x += x & -x; }
	void add(int l, int r, LL v) { add(l, v), add(r + 1, v); }
	LL query(int x) { LL ret = 0; while(x) ret ^= t[x], x -= x & -x; return ret; }
} bit;

LL catalan(int x) { /* printf("catalan %d\n", x); */ return (x & 1) ? 0 : C(x, x / 2) * inv(x / 2 + 1) % MOD; }

int main() {
	get_factorial(3e5);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= K; i++) scanf("%d%d", &a[i].l, &a[i].r);
		a[++K] = {1, n};
		for(int i = 1; i <= n; i++) bit.t[i] = 0;
		for(int i = 1; i <= K; i++) bit.add(a[i].l, a[i].r, (LL)rand() << 45 | (LL)rand() << 30 | rand() << 15 | rand());
		// for(int i = 1; i <= n; i++) printf("%d ", bit.query(i));
		// puts("");
		std::map<LL, int> mp;
		for(int i = 1; i <= n; i++) mp[bit.query(i)]++;
		LL ans = 1;
		for(auto &p : mp) (ans *= catalan(p.second)) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
} /*
1
10 3
1 6
3 8
5 10
*/