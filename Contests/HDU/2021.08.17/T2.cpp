#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int **a;
int n, m;
long long K;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%lld", &n, &m, &K);
		a = new int *[n + 5]; // 分配空间
		for(int i = 1; i <= n; i++) a[i] = new int[m + 5]; // 分配空间
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
		int mx = -INF;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) mx = std::max(mx, a[i][j]);
		if(K == 1) {
			int ans = -INF;
			for(int j = 1; j <= m; j++) ans = std::max(ans, a[1][j]);
			printf("%d\n", std::max(ans, mx));
		} else {
			int ans = -INF;
			for(int j = 1; j <= m; j++) {
				int ret = INF;
				for(int i = 1; i <= n; i++) ret = std::min(ret, a[i][j]);
				ans = std::max(ans, ret);
			}
			printf("%d\n", std::max(mx, ans));
		}
		for(int i = 1; i <= n; i++) delete[] a[i]; // 释放空间
		delete[] a; // 释放空间
	}
	return 0;
}