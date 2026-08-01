#include <cstdio>

#define total(l, r) ((l) > (r) ? 0LL : (((l) + (r)) * ((r) - (l) + 1) / 2))

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		long long l, r;
		scanf("%lld%lld", &l, &r);
		// a + b = c
		// for a = [l .. r - l], b = [l .. r - a] => r - a - l + 1
		printf("%lld\n", total(r - (r - l) - l + 1, r - l - l + 1));
	}
	return 0;
}