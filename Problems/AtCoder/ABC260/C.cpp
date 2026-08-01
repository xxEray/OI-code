#include <cstdio>
#include <algorithm>

typedef long long LL;

LL n, A, B;

int main() {
	scanf("%lld%lld%lld", &n, &A, &B);
	LL x = 1, y = 0;
	for(int i = n; i > 1; i--) {
		LL nx = 0, ny = 0;
		nx += x, y += x * A;
		nx += y, ny += y * B;
		x = nx, y = ny;
	}
	printf("%lld\n", y);
	return 0;
}