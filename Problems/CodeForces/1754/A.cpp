#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 5;

int n;
int a[N], v[N];

std::vector<std::pair<int, int>> ans;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		int sum = 0;
		for(int i = 1; i <= n; i++) sum += a[i];
		if(sum & 1) { puts("-1"); continue; }
		ans.clear();
		for(int i = 2; i <= n + 1;)
			if(i == n + 1) ans.emplace_back(n, n), i++;
			else if((sum > 0 && a[i] == 1) || (sum < 0 && a[i] == -1)) ans.emplace_back(i - 1, i), sum += (sum > 0 ? -2 : 2), i += 2;
			else ans.emplace_back(i - 1, i - 1), i += 1;
		printf("%d\n", (int)ans.size());
		for(auto p : ans) printf("%d %d\n", p.first, p.second);
	}
	return 0;
}