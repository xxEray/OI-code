#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <bitset>
#include <cassert>

const int N = 6e3 + 5;

int n;
std::bitset<2 * N> a[N];

char s[N];

namespace Solve_n1000 {
	void main() {
		for(int i = 1; i <= n + 1; i++) for(int j = i + 1; j <= n + 1; j++)
			if((int)(a[i] & a[j]).count() >= n / 2) {
				printf("%d %d\n", i, j);
				exit(0);
			}
		puts("conflict");
	}
}

namespace Solve_all {
	void main() {
		while(clock() / (double)CLOCKS_PER_SEC <= 0.97) {
			int x = rand() % (n + 1) + 1, y = rand() % (n + 1) + 1;
			if((int)(a[x] & a[y]).count() >= n / 2) {
				if(x > y) std::swap(x, y);
				printf("%d %d\n", x, y);
				exit(0);
			}
		}
		puts("conflict");
	}
}

int main() {
#ifndef DEBUG
	freopen("consensus.in", "r", stdin);
	freopen("consensus.out", "w", stdout);
#endif
	srand(time(0));
	scanf("%d", &n);
	for(int i = 1; i <= n + 1; i++) {
		scanf("%s", s);
		int len = strlen(s);
		for(int j = 0; j < len; j++)
			for(int k = 0; k < 6 && j * 6 + k + 1 <= 2 * n; k++)
				a[i][j * 6 + k + 1] = (s[j] - 33) >> k & 1;
//		assert((int)a[i].count() == n);
	}
	if(n <= 1000) Solve_n1000::main();
	else Solve_all::main();
	return 0;
}
