#include <cstdio>
#include <algorithm>

const int N = 1000 + 5;

struct Node { int math, english, id, ok; } a[N];
int n, x, y, z;

int main() {
	scanf("%d%d%d%d", &n, &x, &y, &z);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i].math), a[i].id = i;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i].english);
	std::sort(a + 1, a + n + 1, [](Node x, Node y) { return x.math == y.math ? x.id < y.id : x.math > y.math; });
	std::sort(a + x + 1, a + n + 1, [](Node x, Node y) { return x.english == y.english ? x.id < y.id : x.english > y.english; });
	std::sort(a + x + y + 1, a + n + 1, [](Node x, Node y) { return x.math + x.english == y.math + y.english ? x.id < y.id : x.math + x.english > y.math + y.english; });
	for(int i = 1; i <= x + y + z; i++) a[i].ok = 1;
	std::sort(a + 1, a + n + 1, [](Node x, Node y) { return x.id < y.id; });
	for(int i = 1; i <= n; i++) if(a[i].ok) printf("%d\n", i);
	return 0;
}