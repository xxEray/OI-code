#include <cstdio>
#include <algorithm>

int main() {
	long long x;
	scanf("%lld", &x);
	if(x < 64) puts((1LL << x) > (x * x) ? "Yes" : "No");
	else puts("Yes");
	return 0;
}