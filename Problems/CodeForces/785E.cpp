#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long long LL;

const int N = 2e5 + 5;

int a[N];
int n, Q;

int block[N], tmp[N], ind[N];
LL ans = 0;

int main() {
	std::scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) a[i] = i, ind[i] = i, tmp[i] = a[i];
	int sz = sqrt(n);
	for(int i = 1; i <= n; i++) block[i] = (i - 1) / sz + 1;
	while(Q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		x = ind[x], y = ind[y];
		if(x > y) std::swap(x, y);
		if(block[x] == block[y]) {
			for(int i = x + 1; i <= y - 1; i++) ans += (a[i] > a[y] ? -1 : (a[i] < a[y])) + (a[i] < a[x] ? -1 : (a[i] > a[x]));
		} else {
			for(int i = (block[y] - 1) * sz + 1; i < y; i++) ans += (a[i] > a[y] ? -1 : (a[i] < a[y]));
			for(int i = x + 1; i <= block[x] * sz; i++) ans += (a[i] > a[y] ? -1 : (a[i] < a[y]));
			for(int i = block[x] + 1; i <= block[y] - 1; i++) {
				int l = (i - 1) * sz + 1, r = i * sz;
				int k = std::upper_bound(tmp + l, tmp + r + 1, a[y]) - tmp - l;
				// printf("k = %d, l = %d, r = %d, a[y] = %d\n", k, l, r, a[y]);
				ans += 2 * k - sz;
			}
			for(int i = (block[y] - 1) * sz + 1; i < y; i++) ans += (a[i] < a[x] ? -1 : (a[i] > a[x]));
			for(int i = x + 1; i <= block[x] * sz; i++) ans += (a[i] < a[x] ? -1 : (a[i] > a[x]));
			for(int i = block[x] + 1; i <= block[y] - 1; i++) {
				int l = (i - 1) * sz + 1, r = i * sz;
				int k = std::upper_bound(tmp + l, tmp + r + 1, a[x]) - tmp - l;
				// printf("k = %d, l = %d, r = %d, a[x] = %d\n", k, l, r, a[x]);
				ans += sz - 2 * k;
			}
		}
		ans += (a[x] > a[y] ? -1 : (a[x] < a[y]));
		ind[a[x]] = y, ind[a[y]] = x;
		std::swap(a[x], a[y]);
		int l = (block[x] - 1) * sz + 1, r = std::min(block[x] * sz, n);
		for(int i = l; i <= r; i++) tmp[i] = a[i];
		std::sort(tmp + l, tmp + r + 1);
		l = (block[y] - 1) * sz + 1, r = std::min(block[y] * sz, n);
		for(int i = l; i <= r; i++) tmp[i] = a[i];
		std::sort(tmp + l, tmp + r + 1);
		printf("%lld\n", ans);
		// for(int i = 1; i <= n; i++) printf("%d ", a[i]);
		// printf("\n");
	}
	return 0;
} /*
42 42
23 7
9 6
17 22
19 23
15 42
*/