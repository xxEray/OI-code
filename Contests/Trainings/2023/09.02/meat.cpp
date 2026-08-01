#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 1e9 + 7;

int n, m;
LL a[N];
std::vector<int> to[N];

bool exist[N];

std::vector<int> order;
LL cnt[N], sum[N];

int main() {
#ifndef DEBUG
	freopen("meat.in", "r", stdin);
	freopen("meat.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[u].push_back(v), to[v].push_back(u); }
	for(int i = 1; i <= n; i++) order.push_back(i);
	std::sort(order.begin(), order.end(), [&](int x, int y) { return to[x].size() > to[y].size(); });
	for(int i = 1; i <= n; i++) exist[i] = true;
	LL ans = 0;
	for(int i : order) {
		for(int j : to[i]) if(exist[j])
			for(int k : to[j]) if(exist[k] && k != i) {
				(ans += cnt[k] * (a[i] + a[j] + a[k]) % MOD + sum[k]) %= MOD;
				cnt[k]++, (sum[k] += a[j]) %= MOD;
			}
		for(int j : to[i]) if(exist[j])
			for(int k : to[j]) if(exist[k] && k != i)
				cnt[k] = sum[k] = 0;
		exist[i] = false;
	}
	printf("%lld\n", ans);
	return 0;
}
