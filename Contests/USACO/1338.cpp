#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m, K;
struct Node { int a, w; } a[N];

std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;

int main() {
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].w, &a[i].a);
	std::sort(a + 1, a + n + 1, [&](const Node &x, const Node &y) { return x.w < y.w; });
	LL ans = 0;
	q.emplace(-INF, m);
	for(int i = 1; i <= n; i++) {
		int cn = 0;
		while(!q.empty() && a[i].a) {
			auto [w_, a_] = q.top();
			// printf("(%d, %d) (%d, %d)\n", a[i].w, a[i].a, w_, a_);
			if(a[i].w - w_ < K) break;
			if(a_ < a[i].a) {
				ans += a_, a[i].a -= a_;
				q.pop();
				cn += a_;
			} else {
				ans += a[i].a;
				q.pop();
				if(a_ - a[i].a) q.emplace(w_, a_ - a[i].a);
				cn += a[i].a, a[i].a = 0;
				break;
			}
		}
		if(cn) q.emplace(a[i].w, cn);
		// printf("i = %d, ans = %lld\n", i, ans);
	}
	printf("%lld\n", ans);
	return 0;
}