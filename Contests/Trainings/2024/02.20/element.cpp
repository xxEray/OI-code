#include <bits/stdc++.h>

const int MOD = 1e9 + 7;

int n, Q;
std::vector<int> a;

namespace Subtask1 {
	void main() {
		for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); a.emplace_back(x); }
		while(Q--) {
			int t, x, y;
			scanf("%d", &t);
			if(t == 1) {
				scanf("%d%d", &x, &y);
				std::vector<int> vct(a.begin() + (x - 1), a.begin() + y);
				std::sort(vct.begin(), vct.end());
				vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
				int ans = 0, sz = vct.size();
				for(int i = 0; i < sz; i++)
					for(int j = i + 1; j < sz; j++)
						for(int k = j + 1; k < sz; k++)
							(ans += (long long)vct[i] * vct[j] % MOD * vct[k] % MOD) %= MOD;
				printf("%d\n", ans);
			} else if(t == 2) {
				scanf("%d%d", &x, &y);
				a[x - 1] = y;
			} else if(t == 3) {
				scanf("%d", &x);
				a.erase(a.begin() + (x - 1));
			} else if(t == 4) {
				scanf("%d%d", &x, &y);
				a.insert(a.begin() + x, y);
			} else if(t == 5) {
				scanf("%d%d", &x, &y);
				std::vector<int> vct(a.begin() + (x - 1), a.begin() + y);
				std::sort(vct.begin(), vct.end());
				vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
				printf("%d\n", (int)vct.size());
			}
		}
	}
}

int main() {
#ifndef DEBUG
	freopen("element.in", "r", stdin);
	freopen("element.out", "w", stdout);
#endif
	scanf("%d%d", &n, &Q);
	if(std::max(n, Q) <= 100) Subtask1::main();
	return 0;
}
