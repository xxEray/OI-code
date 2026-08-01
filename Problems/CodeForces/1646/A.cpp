#include <cstdio>
#include <algorithm>

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		long long n, s;
		scanf("%lld%lld", &n, &s);
		printf("%lld\n", s / (n * n));
	}
	return 0;
}