#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>

const int N = 1000 + 5;

int a[N], b[N], id[N];
int n;

std::vector<std::pair<std::deque<int>, std::deque<int>>> ans;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		int cnt = 0;
		for(int i = 1; i <= n; i++) scanf("%1d", &b[i]), cnt += b[i];
		int m = 0;
		for(int i = 1, j = 0; i <= n; i++, m = j) if(!b[i] || i < n - cnt + 1) j++, a[j] = b[i], id[j] = i;
		n = m, cnt = 0;
		for(int i = 1; i <= n; i++) cnt += a[i];
		// printf("n = %d\n", n);
		// for(int i = 1; i <= n; i++) printf("%d", a[i]);
		// puts("");
		ans.clear();
		for(int i = 1, j = 0; i <= n; i++) {
			j += a[i];
			if(!a[i]) continue;
			int k = n - (cnt - j + 1) + 1;
			if(i == k) continue;
			else if(!ans.empty() && i <= ans.back().second.front()) {
				ans.back().first.push_back(i);
				if(i == ans.back().second.front()) ans.back().second.pop_front();
				ans.back().second.push_back(k);
			} else ans.push_back({{i}, {k}});
		}
		printf("%d\n", (int)ans.size());
		for(auto it = ans.rbegin(); it != ans.rend(); it++) {
			printf("%d ", (int)(it->first.size() + it->second.size()));
			for(auto &j : it->first) printf("%d ", id[j]);
			for(auto &j : it->second) printf("%d ", id[j]);
			puts("");
		}
	}
	return 0;
} /*
1
6
101010
*/