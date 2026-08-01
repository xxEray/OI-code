#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n;
struct Node { int a, b; } a[N];

std::vector<int> b[N];

int main() {
	int T; scanf("%d", &T);
	// bool is_test_2 = (T == 10000);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i].a);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i].b);
		// if(is_test_2 && T == 10000 - 158) {
		// 	printf("%d\n", n);
		// 	for(int i = 1; i <= n; i++) printf("%d ", a[i].a);
		// 	puts("");
		// 	for(int i = 1; i <= n; i++) printf("%d ", a[i].b);
		// 	puts("");
		// }
		std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.a < y.a; });
		for(int i = 1; i <= n; i++) b[i].clear();
		for(int i = 1; i <= n; i++) b[a[i].a].push_back(a[i].b);
		for(int i = 1; i <= n; i++) std::sort(b[i].begin(), b[i].end());
		LL ans = 0;
		for(int i = 1; (LL)i * i <= 2 * n && i <= n; i++) for(int x : b[i]) ans += std::upper_bound(b[i].begin(), b[i].end(), i * i - x) - std::lower_bound(b[i].begin(), b[i].end(), i * i - x);
		for(int i = 1; i <= n; i++) ans -= ((LL)a[i].a * a[i].a == a[i].b + a[i].b);
		// printf("ans = %lld\n", ans);
		assert(ans % 2 == 0);
		ans /= 2;
		for(int i = 1; i <= n; i++)
			for(int j = i + 1; (LL)i * j <= 2 * n && j <= n; j++) {
				int ii = i, jj = j;
				if(b[ii].size() > b[jj].size()) std::swap(ii, jj);
				for(int x : b[ii]) ans += std::upper_bound(b[jj].begin(), b[jj].end(), i * j - x) - std::lower_bound(b[jj].begin(), b[jj].end(), i * j - x);
			}
		// if(is_test_2) continue;
		printf("%lld\n", ans);
	}
	return 0;
} /*
3
3
2 3 2
3 3 1
8
4 2 8 2 1 2 7 5
3 5 8 8 1 1 6 5
8
4 4 8 8 8 8 8 8
8 8 8 8 8 8 8 8

*/