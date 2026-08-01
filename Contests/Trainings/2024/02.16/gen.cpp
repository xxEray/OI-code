#include <cstdint>
#include <testlib.h>

const int N = 1e5;
const int M = 1e5;
const bool remain_unchanged = false;

int a[N + 5];

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	int n = N, m = M;
	freopen("lamp.in", "w", stdout);
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) printf("%d %d\n", rnd.next(0, 1), a[i] = (i == 1 ? rnd.next(2, n) : rnd.next(1, i - 1)));
	printf("%d\n", m);
	for(int i = 1; i <= m; i++) {
		int x = rnd.next(1, n), y = rnd.next(0, 1), z;
		if(remain_unchanged) z = a[x];
		else z = (x == 1 ? rnd.next(2, n) : rnd.next(1, x - 1));
		printf("%d %d %d\n", x, y, z);
	}
	return 0;
}