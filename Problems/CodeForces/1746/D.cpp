#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, K;
int fa[N], s[N];
std::vector<int> to[N];

std::map<std::pair<int, int>, std::pair<LL, LL>> mp;
std::pair<LL, LL> dfs(int u, int k) {
	if(mp.count({u, k})) return mp[{u, k}];
	auto &ans = mp[{u, k}];
	int sz = to[u].size();
	if(!sz) return ans = {(LL)s[u] * k, s[u]};
	int base = k / sz, extra = k - base * sz;
	ans.first = (LL)s[u] * k;
	std::vector<LL> vct;
	for(int v : to[u]) {
		auto p = dfs(v, base);
		ans.first += p.first;
		vct.push_back(p.second);
	}
	std::sort(vct.begin(), vct.end(), [](LL x, LL y) { return x > y; });
	for(int i = 0; i < extra; i++) ans.first += vct[i];
	ans.second = s[u] + vct[extra];
	return ans;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		mp.clear();
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= n; i++) to[i].clear();
		for(int i = 2; i <= n; i++) scanf("%d", &fa[i]), to[fa[i]].push_back(i);
		for(int i = 1; i <= n; i++) scanf("%d", &s[i]);
		printf("%lld\n", dfs(1, K).first);
	}
	return 0;
}