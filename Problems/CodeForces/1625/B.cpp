#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int a[N];
int n;

std::map<int, std::vector<int>> mp;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(auto &p : mp) std::vector<int> ().swap(p.second);
		mp.clear();
		int ans = -INF;
		for(int i = 1; i <= n; i++) mp[a[i]].push_back(i);
		for(auto &p : mp) {
			auto &v = p.second;
			for(int i = 0; i < (int)v.size() - 1; i++)
				ans = std::max(ans, v[i] + n - v[i + 1]);
		}
		printf("%d\n", ans == -INF ? -1 : ans);
	}
	return 0;
}