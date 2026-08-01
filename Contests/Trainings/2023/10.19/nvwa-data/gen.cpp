#include <testlib.h>
#include <cassert>

typedef long long LL;

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	LL n = opt<LL>("n");
	int T = opt<int>("T");
	printf("%lld %d\n", n, T);
	LL V = opt<LL>("V");
	assert((__int128_t)T * V <= 1000000000000000000);
	for(int t = 1; t <= T; t++) {
		LL l = rnd.next(1LL, n);
		LL r = l + rnd.next(0LL, std::min(n - l, 1000000000000000000 / T / V));
		LL d = rnd.next(1LL, V);
		printf("%lld %lld %lld\n", l - 1, r, d);
	}
	return 0;
}