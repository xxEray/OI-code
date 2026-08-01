#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
int a[N];

std::priority_queue<int, std::vector<int>, std::greater<int>> q;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	LL ans = (m == 0 ? -LLINF : 0LL);
	for(int i = 1; i <= n - m + 1; i++) {
		LL sum = 0;
		for(int j = i; j <= i + m - 1; j++) q.emplace(a[j]);
		for(int j = i + m; j <= n; j++) {
			q.emplace(a[j]);
			sum += q.top(), q.pop();
			ans = std::max(ans, sum);
		}
	}
	printf("%lld\n", ans);
	return 0;
}