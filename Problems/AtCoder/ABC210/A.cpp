#include <cstdio>
#include <algorithm>

int main() {
	int n, a, x, y;
	scanf("%d%d%d%d", &n, &a, &x, &y);
	printf("%d\n", n <= a ? x * n : x * a + y * (n - a));
	return 0;
}