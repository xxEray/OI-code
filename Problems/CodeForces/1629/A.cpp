#include <cstdio>
#include <algorithm>

const int N = 100 + 5;

struct Node { int a, b; } a[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int now;
		scanf("%d%d", &n, &now);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i].a);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i].b);
		std::sort(a + 1, a + n + 1, [](Node x, Node y) { return x.a < y.a; });
		for(int i = 1; i <= n; i++) if(a[i].a <= now) now += a[i].b;
		printf("%d\n", now);
	}
	return 0;
}