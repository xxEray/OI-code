#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#include <vector>

typedef long long LL;

const int N = 3e5 + 5;

std::map<LL, LL> mp;
std::set<std::pair<LL, LL>> st;
std::vector<LL> occur[N];
int n, m;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		mp.clear(), st.clear();
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) occur[i].clear();
		for(int i = 1; i <= n; i++) { LL x; scanf("%lld", &x), mp[x]++; }
		for(int i = 1; i <= m; i++) { LL x, y; scanf("%lld%lld", &x, &y); st.insert({x, y}), st.insert({y, x}); }
		for(auto p : mp) occur[p.second].push_back(p.first);
		for(int i = 1; i <= n; i++) std::reverse(occur[i].begin(), occur[i].end());
		LL ans = 0;
		for(int ci = 1; ci <= n; ci++) for(int i : occur[ci])
			for(int cj = 1; cj <= ci; cj++) for(int j : occur[cj])
				if(i != j && st.find({i, j}) == st.end())
					{ ans = std::max(ans, (LL)(i + j) * (ci + cj)); break; }
		printf("%lld\n", ans);
	}
	return 0;
}