#include "testlib.h"

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	int n = opt<int>("n"), m = opt<int>("m"), K = opt<int>("K");
	printf("%d %d %d\n", n, m, K);
	for(int i = 2; i <= n; i++) printf("%d %d\n", rnd.next(1, i - 1), i);
	for(int i = 1; i <= m; i++) {
		int u = rnd.next(1, n), v = rnd.next(1, n);
		while(u == v) u = rnd.next(1, n), v = rnd.next(1, n);
		printf("%d %d\n", u, v);
	}
	return 0;
}