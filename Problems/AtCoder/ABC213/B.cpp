#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

struct Node { int v, id; } a[N];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i].v), a[i].id = i;
	std::sort(a + 1, a + n + 1, [](Node a, Node b) { return a.v > b.v; });
	printf("%d\n", a[2].id);
	return 0;
}