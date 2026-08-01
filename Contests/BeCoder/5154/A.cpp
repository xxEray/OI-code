#include <bits/stdc++.h>

typedef long long LL;

LL n, m;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld", &n, &m);
		if(n * (n + 1) / 2 % 2 == 0) {
			puts("Yes");
			LL val = n * (n + 1) / 4 - n;
			std::vector<int> vct;
			int cnt = n;
			for(LL i = n; i >= 2; i--)
				while(val >= i * (i - 1) / 2) val -= i * (i - 1) / 2, cnt -= i, vct.emplace_back(i);
			while(cnt--) vct.emplace_back(1);
			for(int i = 0; i < (int)vct.size(); i++)
				while(vct[i]--) {
					for(int _ = 1; _ <= m; _++) printf("%d ", i & 1);
					puts("");
				}
		} else if(m * (m + 1) / 2 % 2 == 0) {
			puts("Yes");
			LL val = m * (m + 1) / 4 - m;
			std::vector<int> vct;
			int cnt = m;
			for(LL i = m; i >= 2; i--)
				while(val >= i * (i - 1) / 2) val -= i * (i - 1) / 2, cnt -= i, vct.emplace_back(i);
			while(cnt--) vct.emplace_back(1);
			for(int i = 1; i <= n; i++) {
				for(int j = 0; j < (int)vct.size(); j++) for(int _ = 1; _ <= vct[j]; _++) printf("%d ", j & 1);
				puts("");
			}
		} else puts("No");
	}
	return 0;
}