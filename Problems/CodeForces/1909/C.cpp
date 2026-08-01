#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n;
int b[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		std::vector<std::pair<int, int>> seq;
		for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); seq.emplace_back(x, 0); }
		for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); seq.emplace_back(x, 1); }
		for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
		std::sort(seq.begin(), seq.end());
		std::vector<int> stk, vct;
		for(auto [i, t] : seq)
			if(t == 0) stk.emplace_back(i);
			else vct.emplace_back(i - stk.back()), stk.pop_back();
		std::sort(vct.begin(), vct.end()), std::sort(b + 1, b + n + 1, std::greater<int>());
		LL ans = 0;
		for(int i = 1; i <= n; i++) ans += (LL)vct[i - 1] * b[i];
		printf("%lld\n", ans);
	}
	return 0;
}