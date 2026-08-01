#include <cstdio>
#include <algorithm>

int main() {
	int n;
	scanf("%d", &n);
	n = n + 99999;
	int a = n / 100000, b = n / 10000 % 10, c = n / 1000 % 10, d = n / 100 % 10, e = n / 10 % 10, f = n % 10;
	printf("%d%d%d%d%d%d%d%d%d\n", a, a, b, c, d, d, e, f, e);
	return 0;
}