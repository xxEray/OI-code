#include <cstdio>
#include <algorithm>

typedef long long LL;

LL a, b;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld", &a, &b);
		if(a < b) std::swap(a, b);
		LL g = a - b;
		LL h = (g == 0 ? 0 : std::min(a % g, g - a % g));
		printf("%lld %lld\n", g, h);
	}
	return 0;
}