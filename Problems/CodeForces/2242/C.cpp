#include <bits/stdc++.h>

const int N = 3e5 + 5;

int n, K;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &K);
		std::vector<int> cnt;
		int last = 0, tot = 0;
		for(int i = 1; i <= n; i++) {
			int x;
			scanf("%d", &x);
			if(x == last) tot++;
			else {
				cnt.emplace_back(tot);
				last = x, tot = 1;
			}
		}
		cnt.emplace_back(tot);
		std::sort(cnt.begin(), cnt.end());
		// for(int x : cnt) printf("%d ", x);
		// puts("");
		int sum = 0, sz = cnt.size(), ans = 0;
		for(int i = 0; i < sz - 1; i++) {
			sum += cnt[i];
			if(i + 1 < sz && cnt[i] == cnt[i + 1]) continue;
			int rest = n - sum - (sz - 1 - i) * cnt[i];
			if(K - rest >= 0) ans += ((K - rest) % (sz - 1 - i) == 0);
			else {
				if((rest - K) % (sz - 1 - i) == 0 && i + 1 < sz)
					ans += ((rest - K) / (sz - 1 - i) < cnt[i + 1] - cnt[i]);
			}
			// printf("i = %d, ans = %d\n", i, ans);
		}
		printf("%d\n", ans);
	}
	return 0;
}