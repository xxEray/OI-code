#include <cstdio>
#include <algorithm>

typedef long long LL;

LL u, v;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld", &u, &v);
		printf("%lld %lld\n", -u * u, v * v);
	}
	return 0;
}