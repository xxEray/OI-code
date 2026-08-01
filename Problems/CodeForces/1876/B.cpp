#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 998244353;

int n;
int a[N];

int f[N];
bool vis[N];
std::vector<int> vct[N], tin[N];

LL power2[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	power2[0] = 1;
	for(int i = 1; i <= 100000; i++) power2[i] = power2[i - 1] * 2 % MOD;
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j += i)
			vct[j].push_back(i);
	for(int i = 1; i <= n; i++) tin[a[i]].push_back(i);
	int cnt = n;
	for(int i = 100001; i >= 0; i--) {
		for(int j : tin[i])
			for(int k : vct[j])
				if(!vis[k]) cnt--, vis[k] = true;
		f[i] = cnt;
	}
	LL ans = 0;
	for(int i = 1; i <= 100000; i++) (ans += i * (power2[f[i + 1]] - power2[f[i]] + MOD)) %= MOD;
	printf("%lld\n", ans);
	return 0;
}