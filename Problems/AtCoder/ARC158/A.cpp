#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

LL x, y, z;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld%lld", &x, &y, &z);
		if((x + y + z) % 3) { puts("-1"); continue; }
		LL target = (x + y + z) / 3;
		if(std::abs(x - target) % 2 || std::abs(y - target) % 2 || std::abs(z - target) % 2) { puts("-1"); continue; }
		printf("%lld\n", (std::abs(x - target) / 2 + std::abs(y - target) / 2 + std::abs(z - target) / 2) / 2);
	}
	return 0;
}