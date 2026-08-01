#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;
const LL MOD = 998244353;

int n, m;

std::set<std::pair<int, int>> st;

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

int d[N];
int fa[N], cnt[N], sz[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? (fa[x] = y, cnt[y] += cnt[x]) : 0; }

int main() {
#ifndef DEBUG
	freopen("per.in", "r", stdin);
	freopen("per.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	get_factorial(n);
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		if(st.count({u, v})) continue;
		st.insert({u, v}), st.insert({v, u});
		d[u]++, d[v]++;
		if(d[u] >= 3 || d[v] >= 3) { puts("0"); return 0; }
		merge(u, v);
		cnt[find(u)]++;
	}
	int cycle = 0, chain = 0, chain2 = 0, single = 0;
	for(int i = 1; i <= n; i++) sz[find(i)]++;
	for(int i = 1; i <= n; i++) if(find(i) == i) {
		if(cnt[find(i)] == sz[find(i)]) cycle += (sz[find(i)] > 2);
		else if(sz[find(i)] > 2 && cnt[find(i)] == sz[find(i)] - 1) chain++;
		else if(sz[find(i)] == 2) chain2++;
		else single++;
	}
	// printf("cycle = %d, chain = %d, chain2 = %d, single = %d\n", cycle, chain, chain2, single);
	LL ans = 0;
	for(int i = 0; i <= chain2; i++)
		(ans += ((i & 1) ? MOD - 1 : 1) * C(chain2, i) % MOD * qpow(2, chain2 - i) % MOD * fac[single + chain + chain2 - i]) %= MOD;
	printf("%lld\n", ans * qpow(2, cycle + chain) % MOD);
	return 0;
} /*
4 4
3 4
1 2
2 1
2 1
*/