#include <cstdio>
#include <algorithm>

typedef long long LL;

LL n, A, B;

int main() {
	scanf("%lld%lld%lld", &n, &A, &B);
	if(n < A) { puts("0"); return 0; }
	if(B >= A) { printf("%lld\n", n - A + 1); return 0; }
	LL ans = 0;
	LL m = n / A * A;
	ans += m / A * B - B;
	m = n % A;
	ans += std::min(m, B - 1) + 1;
	printf("%lld\n", ans);
	return 0;
}