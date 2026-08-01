#include <cstdio>
#include <algorithm>

int main() {
	long long x;
	scanf("%lld", &x);
	printf("%lld\n", x > 0 ? x / 10 : -((-x + 9) / 10));
	return 0;
}