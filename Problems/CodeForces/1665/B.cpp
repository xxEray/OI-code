#include <cstdio>
#include <algorithm>
#include <map>

const int N = 1e5 + 5;

int a[N];
int n;
std::map<int, int> mp;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		mp.clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), mp[a[i]]++;
		int mx = 0;
		for(auto p : mp) mx = std::max(mx, p.second);
		int ret = mx, ans = n - mx;
		while(ret < n) ret *= 2, ans++;
		printf("%d\n", ans);
	}
	return 0;
}