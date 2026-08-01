#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

struct Node { int l, r; } a[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r);
		std::sort(a + 1, a + n + 1, [](Node x, Node y) { return x.l < y.l; });
		int ans = 0;
		a[n + 1].l = a[n].r + 1;
		for(int i = 1; i <= n; i++)
			if(a[i].r < a[i + 1].l) ans++;
			else break;
		printf("%d\n", ans);
	}
	return 0;
}