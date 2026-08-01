#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int n, d, x, y;

const int dirx[] = {0, 1,  0, -1};
const int diry[] = {1, 0, -1,  0};
inline void forward(int step) { while(step--) putchar('f'), x += dirx[d], y += diry[d]; }
// inline void turn_to(int x) { while(d != x) d = (d + 1) % 4, putchar('c'); }

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d%d", &x, &y, &d, &n);
		for(int i = 1; i <= n; i++) {
			int tx, ty;
			scanf("%d%d", &tx, &ty);
			int dx = (x < tx ? 1 : -1), dy = (y < ty ? 1 : -1);
			while(true) {
				if(dirx[d] == dx) forward(std::abs(tx - x)), x = tx;
				if(diry[d] == dy) forward(std::abs(ty - y)), y = ty;
				if(x == tx && y == ty) break;
				int u = (d - 1 + 4) % 4, c = (d + 1) % 4;
				if(dirx[c] != dx && diry[c] != dy) putchar('u'), d = u;
				else putchar('c'), d = c;
			}
		}
		puts("");
	}
	return 0;
} /*
1
0 0 0 5

*/