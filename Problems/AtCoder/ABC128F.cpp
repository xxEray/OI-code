#include <cstdio>
#include <algorithm>
#include <cassert>

typedef long long LL;

const int N = 1e5 + 5;

LL a[N];
int n;

bool vis[N];

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%lld", &a[i]);
	LL ans = 0;
	for(int C = 1; C <= n; C++) {
		LL sum = 0;
		for(int i = 0; i < n; i++) vis[i] = false;
		vis[0] = vis[n - 1] = true;
		for(int k = 1; k <= (n - 1) / C; k++) {
			int x = n - 1 - k * C, y = k * C;
			int A = x, B = x - C;
			if(vis[x] || vis[y] || x == y || A <= 0 || B <= 0) break;
			assert(0 <= x && x < n && 0 <= y && y < n);
			vis[x] = vis[y] = true;
			sum += a[x] + a[y];
			ans = std::max(ans, sum);
		}
	}
	printf("%lld\n", ans);
	return 0;
}