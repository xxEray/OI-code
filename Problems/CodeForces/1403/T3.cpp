#include <cstdio>
#include <cmath>

const int N = 1000 + 3;
const int MOD = 1e9 + 7;

typedef long long LL;

int n, m, q;

int main() {
	std::scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= q; i++) {
		char t[2];
		int c1, cr;
		std::scanf("%s%d%d", t, &c1, &cr);
		if(*t == 'P') std::printf("%d %d\n", c1 == cr ? n : 0, c1 == cr ? 1 : 0);
		else if(*t == 'R') std::printf("%d %d\n", c1 == cr ? 1 : 2, c1 == cr ? 1 : 2);
		else if(*t == 'Q') {
			if(c1 == cr || std::abs(c1 - cr) == n - 1) std::printf("1 1\n");
			else std::printf("2 %d\n", 4 + (c1 == 1 || c1 == m || cr == 1 || cr == m) + );
		} else if(*t == 'B') {
			std::puts("Unknow");
		} else { // 'K'
			std::puts("Unknow");
		}
	}
	return 0;
} /*
8 8 5
P 1 2
R 4 8
Q 2 3
B 3 6
K 5 5
*/