#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 3e5 + 5;

int n, m;
std::vector<int> a[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i++) a[i].clear(), a[i].shrink_to_fit(), a[i].resize(n + 1);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &a[j][i]);
		LL ans = 0;
		for(int j = 1; j <= m; j++) {
			std::sort(a[j].begin() + 1, a[j].end());
			LL sum = 0;
			for(int i = 1; i <= n; i++) ans += (LL)a[j][i] * (i - 1) - sum, sum += a[j][i];
			sum = 0;
			for(int i = n; i >= 1; i--) ans += sum - (LL)a[j][i] * (n - i), sum += a[j][i];
		}
		printf("%lld\n", ans / 2);
	}
	return 0;
}