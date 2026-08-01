#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 2e5 + 5;

int a[N], b[N];
int n;

std::vector<std::pair<int, int>> va, vb;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%1d", &a[i]);
		for(int i = 1; i <= n; i++) scanf("%1d", &b[i]);
		va.clear(), vb.clear();
		for(int i = 1; i <= n; i++) if(a[i - 1] == 0 && a[i] == 1) {
			int l = i, r = i;
			while(r < n && a[r + 1] == 1) r++;
			va.push_back({l, r});
		}
		for(int i = 1; i <= n; i++) if(b[i - 1] == 0 && b[i] == 1) {
			int l = i, r = i;
			while(r < n && b[r + 1] == 1) r++;
			vb.push_back({l, r});
		}
		if(a[1] != b[1] || a[n] != b[n] || va.size() != vb.size()) { puts("-1"); continue; }
		LL ans = 0;
		for(int i = 0; i < (int)va.size(); i++) ans += std::abs(va[i].first - vb[i].first) + std::abs(va[i].second - vb[i].second);
		printf("%lld\n", ans);
	}
	return 0;
}