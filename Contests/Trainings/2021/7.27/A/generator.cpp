#include <cstdio>
#include <cstdlib>
#include <ctime>

const int N = 1000;

int main(int argc, char *argv[]) {
	if(argc == 1) srand(time(NULL));
	else {
		int r;
		sscanf(argv[1], "%d", &r);
		srand(r);
	}
	printf("%d\n", rand() % N + 1);
	return 0;
}