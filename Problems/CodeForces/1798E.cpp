#include <cstdio>
#include <algorithm>

const int N = 3e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

int g[N];
int f[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) f[i] = g[i] = 0;
		int mx = 0;
		for(int i = n; i >= 1; i--) {
			g[i] = (a[i] < n - i ? g[i + a[i] + 1] + 1 : (a[i] == n - i ? 1 : -INF));
			f[i] = std::max((a[i] < n - i ? f[i + a[i] + 1] + 1 : (a[i] == n - i ? 1 : 0)), mx + 1);
			mx = std::max(mx, g[i]);
		}
		for(int i = 1; i <= n - 1; i++) {
			if(g[i + 1] >= 0 && a[i] == g[i + 1]) printf("0 ");
			else if(g[i + 1] >= 0 || a[i] <= f[i + 1]) printf("1 ");
			else printf("2 ");
		}
		puts("");
	}
	return 0;
}