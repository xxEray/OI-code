#include <cstdio>
#include <algorithm>

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		long long n;
		scanf("%lld", &n);
		printf("%lld %lld\n", -(n - 1), n);
	}
	return 0;
}