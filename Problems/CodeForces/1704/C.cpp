#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int a[N];
int n, m;

int b[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i++) scanf("%d", &a[i]);
		std::sort(a + 1, a + m + 1);
		for(int i = 1; i < m; i++) b[i] = a[i + 1] - a[i] - 1;
		b[m] = a[1] + n - a[m] - 1;
		std::sort(b + 1, b + m + 1);
		// for(int i = 1; i <= m; i++) printf("%d ", b[i]);
		// puts("");
		int minus = 0, ans = 0;
		for(int i = m; i >= 1; i--) {
			b[i] = std::max(b[i] - minus, 0);
			if(!b[i]) break;
			minus += 4, b[i] -= (b[i] == 1 ? 0 : 1);
			ans += b[i];
		}
		printf("%d\n", n - ans);
	}
	return 0;
} /*
1

*/