#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

const int N = 2e5 + 5;

int n, K;
int a[N];

std::map<int, std::vector<int>> mp;

int main() {
#ifndef DEBUG
	freopen("frogga.in", "r", stdin);
	freopen("frogga.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		mp.clear();
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		int mx = 0;
		while(K >= (1 << mx)) mx++;
		for(int i = 1; i <= n; i++) mp[a[i] & ~((1 << mx) - 1)].push_back(a[i]);
		int ans = 0;
		for(auto &p : mp) {
			auto &v = p.second;
			int sz = v.size();
			for(int s = 0; s < (1 << sz); s++) {
				bool flag = true;
				for(int i = 0; i < sz; i++) if(s >> i & 1)
					for(int j = 0; j < sz; j++) if(s >> j & 1)
						flag &= ((v[i] ^ v[j]) <= K);
				if(flag) ans = std::max(ans, __builtin_popcount(s));
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}