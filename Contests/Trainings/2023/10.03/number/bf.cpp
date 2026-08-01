#include <bits/stdc++.h>

typedef long long LL;

const LL MOD = 998244353;

int n, m;

LL ans;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
int lcm(int x, int y) { return x / gcd(x, y) * y; }

int a[100];
void dfs(int i) {
	if(i == n + 1) {
		int g = 0, l = 1;
		for(int j = 1; j <= n; j++) g = gcd(g, a[j]), l = lcm(l, a[j]);
		(ans *= qpow(l, g)) %= MOD;
		return;
	}
	for(int j = 1; j <= m; j++) a[i] = j, dfs(i + 1);
}

int main() {
	scanf("%d%d", &n, &m);
	ans = 1;
	dfs(1);
	printf("%lld\n", ans);
	return 0;
}