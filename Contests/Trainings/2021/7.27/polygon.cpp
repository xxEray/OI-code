#include <cstdio>
#include <algorithm>

int main() {
#ifndef DEBUG
	freopen("polygon.in", "r", stdin);
	freopen("polygon.out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	if(n & 1) puts("0");
	else printf("%d\n", (n - 4) / 2);
	return 0;
}
