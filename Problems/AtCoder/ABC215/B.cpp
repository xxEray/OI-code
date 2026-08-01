#include <cstdio>
#include <algorithm>

long long n;

int main() {
	scanf("%lld", &n);
	long long power = 1, bit = 0;
	while((power << 1) <= n) power <<= 1, bit++;
	printf("%lld\n", bit);
	return 0;
}