#include "testlib.h"

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	int n = opt<int>("n");
	printf("%d\n", rnd.next(std::max(n - 10000, 1), n));
	return 0;
}