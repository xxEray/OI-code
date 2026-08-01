#include <testlib.h>

const int N = 1000 + 5;

int a[N];

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	int n = opt<int>("n");
	bool special = opt<bool>("special");
	for(int i = 1; i <= n; i++) a[i] = i;
	if(special) {
		int i = rnd.next(1, n), j = rnd.next(1, n);
		while(i == j) i = rnd.next(1, n), j = rnd.next(1, n);
		std::swap(a[i], a[j]);
	} else shuffle(a + 1, a + n + 1);
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) printf("%d ", a[i]);
	puts("");
	return 0;
}