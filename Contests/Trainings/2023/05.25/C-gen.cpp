#include <testlib.h>

const int N = 18;
const int VX = 1e8;
const int V = 998244352;
const int M = 100;

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	// freopen("in.txt", "w", stdout);
	int n = N, m = M, K = 2;
	printf("%d %d %d\n", n, m, K);
	for(int i = 1; i <= n; i++) printf("%d ", rnd.next(1, VX));
	puts("");
	for(int i = 1; i <= n; i++) printf("%d ", rnd.next(0, V));
	puts("");
	for(int i = 1; i <= m; i++) {
		int x = rnd.next(1, VX), y = rnd.next(1, VX), z = rnd.wnext(0, 100, 2);
		if(x > y) std::swap(x, y);
		printf("%d %d %d\n", x, y, z);
	}
	return 0;
} /*
while(1) {
	./C-gen $(get-random) | out-file in.txt -encoding utf8
	cat in.txt | ./C > out.txt
	cat in.txt | ./C-std > ans.txt
	fc.exe out.txt ans.txt
	if($? -eq $False) {
		break
	}
}
*/