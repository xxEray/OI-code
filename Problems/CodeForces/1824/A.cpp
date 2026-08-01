#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int n, m;
int a[N], b[N];
int cntl, cntr;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		cntl = 0, cntr = 0;
		int c = 0;
		for(int i = 1; i <= n; i++)
			if(a[i] == -1) cntl++;
			else if(a[i] == -2) cntr++;
			else b[++c] = a[i];
		std::sort(b + 1, b + c + 1);
		n = std::unique(b + 1, b + c + 1) - b - 1;
		// printf("cntl = %d, cntr = %d\n", cntl, cntr);
		// for(int i = 1; i <= n; i++) printf("%d ", b[i]);
		int ans = 0;
		for(int i = 1; i <= n; i++) ans = std::max(ans, n + std::min(b[i] - i, cntl) + std::min((m - b[i]) - (n - i), cntr));
		ans = std::max(ans, n + std::min(m - n, cntl));
		ans = std::max(ans, n + std::min(m - n, cntr));
		printf("%d\n", ans);
	}
	return 0;
}