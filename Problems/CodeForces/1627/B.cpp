#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int n, m;

int a[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int cnt = 0;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
			a[++cnt] = std::max({n - i + m - j, i - 1 + j - 1, n - i + j - 1, i - 1 + m - j});
		std::sort(a + 1, a + n * m + 1);
		for(int i = 1; i <= n * m; i++) printf("%d ", a[i]);
		puts("");
	}
	return 0;
}