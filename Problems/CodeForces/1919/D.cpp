#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
int a[N];

int copy[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		a[n + 1] = 0;
		for(int i = n + 1; i >= 0; i--) a[i] = a[i] - a[i - 1];
		for(int i = 1; i <= n + 1; i++) printf("%d ", a[i]);
		puts("");
		{
			for(int i = 1; i <= n + 1; i++) copy[i] = a[i];
			std::vector<int> stk;
			std::vector<std::pair<int, int>> vct;
			int cnt = 4 * n;
			for(int i = 1; i <= n + 1 && cnt; i++) {
				// printf("i = %d\n", i);
				if(a[i] > 0) {
					while(cnt && a[i]--) stk.emplace_back(i), cnt--;
				} else if(a[i] < 0) {
					a[i] = -a[i];
					while(cnt && !stk.empty() && a[i]) {
						a[i]--;
						int j = stk.back();
						stk.pop_back();
						// printf("(%d, %d)\n", j, i);
						vct.emplace_back(j, i);
					}
					// printf("a[i] = %d\n", a[i]);
					if(a[i]) { cnt = 0; break; }
				}
			}
			if(cnt) {
				std::set<int> lp, rp;
				std::sort(vct.begin(), vct.end(), [&](const std::pair<int, int> &x, const std::pair<int, int> &y) {
					return x.second - x.first > y.second - y.first;
				});
				lp.emplace(1), rp.emplace(n + 1);
				for(auto [l, r] : vct) {
					if(!lp.count(l) && !rp.count(r)) { cnt = 0; break; }
					if(lp.count(l) && rp.count(r)) { cnt = 0; break; }
					lp.emplace(l), rp.emplace(r);
				}
			}
			if(!cnt) { puts("NO"); continue; }
		}
		{
			for(int i = 1; i <= n + 1; i++) a[i] = copy[i];
			std::vector<int> stk;
			std::vector<std::pair<int, int>> vct;
			int cnt = 4 * n;
			for(int i = 1; i <= n + 1 && cnt; i++) {
				// printf("i = %d (%d)\n", i, a[i]);
				if(a[i] > 0) {
					while(cnt && a[i]--) stk.emplace_back(i), cnt--;
				} else if(a[i] < 0) {
					a[i] = -a[i];
					while(cnt && !stk.empty() && a[i]) {
						a[i]--;
						int j = stk.back();
						stk.pop_back();
						// printf("! (%d, %d)\n", j, i);
						vct.emplace_back(j, i);
					}
					// printf("a[i] = %d\n", a[i]);
					if(a[i]) { cnt = 0; break; }
				} else {
					if(i == 1 || i == n + 1) continue;
					if(stk.empty()) { cnt = 0; break; }
					vct.emplace_back(stk.back(), i);
					stk.pop_back();
					stk.emplace_back(i);
				}
			}
			if(cnt) {
				std::set<int> lp, rp;
				std::sort(vct.begin(), vct.end(), [&](const std::pair<int, int> &x, const std::pair<int, int> &y) {
					return x.second - x.first > y.second - y.first;
				});
				lp.emplace(1), rp.emplace(n + 1);
				for(auto [l, r] : vct) {
					// printf("(%d, %d)\n", l, r);
					lp.emplace(l), rp.emplace(r);
				}
				for(int i = 2; i <= n; i++) if(!lp.count(i) && !rp.count(i)) { cnt = 0; break; }
			}
			if(!cnt) { puts("NO"); continue; }
		}
		puts("YES");
	}
	return 0;
}