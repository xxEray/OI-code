#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 18 + 3;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL a[N];
int n;

LL dfs(int l, int r, LL x, LL y) {
	if(l + 1 == r) return 0;
	LL ret = LLINF;
	for(int i = l + 1; i <= r - 1; i++)
		ret = std::min(ret, dfs(l, i, x, x + y) + dfs(i, r, x + y, y) + a[i] * (x + y));
	return ret;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	printf("%lld\n", a[1] + a[n] + dfs(1, n, 1, 1));
	return 0;
} /*
6
5 2 4 1 6 9
*/