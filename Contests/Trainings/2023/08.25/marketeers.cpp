#include <bits/stdc++.h>

const int N = 5e5 + 5;
const int MOD = 998244353;

int n;
std::set<int> a[N];
std::vector<int> d[N];
int b[N];
int order[N];

std::vector<int> f[N];

int main() {
#ifndef DEBUG
	freopen("marketeers.in", "r", stdin);
	freopen("marketeers.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int k, x;
		scanf("%d", &k);
		while(k--) scanf("%d", &x), a[i].insert(x), d[i].push_back(x);
		std::sort(d[i].begin(), d[i].end());
	}
	std::set<int> st;
	b[1] = *a[1].rbegin(), st.insert(b[1]);
	for(int i = 2; i <= n; i++) {
		int x = *a[i].begin();
		auto it = st.upper_bound(x);
		if(it == st.end()) b[i] = *a[i].rbegin();
		else b[i] = *--a[i].lower_bound(*it);
		st.insert(b[i]);
	}
	// printf("b: "); for(int i = 1; i <= n; i++) printf("%d ", b[i]); puts("");
	for(int i = 1; i <= n; i++) order[i] = i;
	std::sort(order + 1, order + n + 1, [&](int x, int y) { return b[x] == b[y] ? x > y : b[x] > b[y]; });
	// printf("order: "); for(int i = 1; i <= n; i++) printf("%d ", order[i]); puts("");
	for(int i = 1; i <= n; i++) f[i].resize(d[order[i]].size());
	f[0].push_back(1), d[0].push_back(1000000001);
	for(int oi = 1; oi <= n; oi++) {
		int i = order[oi], j = order[oi - 1];
		int ci = d[i].size(), cj = d[j].size();
		int sum = 0;
		for(int k = ci - 1, t = cj; k >= 0; k--) {
			while(t && (d[j][t - 1] > d[i][k] || (i < j && d[j][t - 1] == d[i][k]))) t--, (sum += f[oi - 1][t]) %= MOD;
			f[oi][k] = sum;
		}
		// printf("f[%d]: ", oi); for(int x : f[oi]) printf("%d ", x); puts("");
	}
	int ans = 0;
	for(auto x : f[n]) (ans += x) %= MOD;
	printf("%d\n", ans);
	return 0;
} /*
4
2
2 1
3
5 1 6
1
3
3
6 5 7
*/