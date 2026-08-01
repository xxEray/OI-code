#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

int n, m;

std::vector<int> stk;
LL a[N];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%lld", &a[i]), a[i] += i;
	for(int i = 1; i <= m; i++) {
		LL ans = -1, t = i;
		while(!stk.empty() && a[stk.back()] < a[i]) {
			int j = stk.back();
			ans += (a[j] - t + 1) * (i - j);
			t = a[j] + 1;
			stk.pop_back();
		}
		int j = (stk.empty() ? 0 : stk.back());
		ans += (a[i] - t + 1) * (i - j);
		t = a[j] + 1;
		while(!stk.empty() && a[stk.back()] == a[i]) stk.pop_back();
		stk.push_back(i);
		printf("%lld ", ans);
	}
}