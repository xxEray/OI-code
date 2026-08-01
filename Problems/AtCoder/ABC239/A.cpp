#include <cstdio>
#include <algorithm>
#include <cmath>

int main() {
	int x;
	scanf("%d", &x);
	printf("%.7Lf\n", sqrtl((long long)x * (12800000LL + x)));
	return 0;
}