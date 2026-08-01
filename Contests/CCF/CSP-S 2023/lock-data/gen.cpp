#include "testlib.h"

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	int n = opt<int>("n");
	bool random = opt<bool>("random");
	bool special = opt<bool>("special");
	ensure(!random || !special);
	if(random) {
		printf("%d\n", n);
		for(int i = 1; i <= n; i++) printf("%d %d %d %d %d\n", rnd.next(0, 9), rnd.next(0, 9), rnd.next(0, 9), rnd.next(0, 9), rnd.next(0, 9));
	} else {
		printf("%d\n", n);
		int ans[7];
		ans[0] = rnd.next(0, 9), ans[1] = rnd.next(0, 9), ans[2] = rnd.next(0, 9), ans[3] = rnd.next(0, 9), ans[4] = rnd.next(0, 9);
		int prob[100][7];
		int c = 0;
		for(int i = 0; i < 5; i++) for(int j = 1; j <= 9; j++) {
			c++;
			for(int k = 0; k < 5; k++) prob[c][k] = ans[k];
			(prob[c][i] += j) %= 10;
		}
		if(!special) {
			for(int i = 0; i < 4; i++) for(int j = 1; j <= 9; j++) {
				c++;
				for(int k = 0; k < 5; k++) prob[c][k] = ans[k];
				(prob[c][i] += j) %= 10, (prob[c][i + 1] += j) %= 10;
			}
		}
		for(int i = 1; i <= n; i++) {
			int j = rnd.next(1, c);
			for(int k = 0; k < 5; k++) printf("%d ", prob[j][k]);
			puts("");
		}
	}
	return 0;
}