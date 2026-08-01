#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, m;
struct Node { int cnt, cost; } a[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%de", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i].cnt);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i].cost);
		std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.cost < y.cost; });
		int cnt = 0;
		long long sum = 0;
		for(int i = 1; i <= n; i++) if(a[i].cost <= m) {
			if(cnt + a[i].cnt < n) cnt += a[i].cnt, sum += (long long)a[i].cnt * a[i].cost;
			else {
				sum += (long long)a[i].cost * ((n - 1) - cnt);
				cnt = n - 1;
				break;
			}
		}
		sum += (long long)(n - cnt) * m;
		printf("%lld\n", sum);
	}
	return 0;
}