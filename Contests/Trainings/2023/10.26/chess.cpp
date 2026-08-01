#include <bits/stdc++.h>

int main() {
#ifndef DEBUG
	freopen("chess.in", "r", stdin);
	freopen("chess.out", "w", stdout);
#endif
	int n, m, x1, y1, x2, y2;
	while(scanf("%d%d%d%d%d%d", &n, &m, &x1, &y1, &x2, &y2) == 6) {
		if(std::abs(x1 - x2) + std::abs(y1 - y2) == 1) { puts("-1"); continue; }
		if(n == 3 && m == 3) {
			if(x2 == 2 && y2 == 2) puts("1");
			else if(x1 == 2 && y1 == 2) puts("3");
			else puts("2");
		} else if(n <= 2 && m <= 2) {
			puts("1");
		} else if(n <= 2 || m <= 2) {
			if(std::abs(x1 - x2) == 1 && std::abs(y1 - y2) == 1) {
				if((n > 2 && x2 > 2 && x2 < n - 1) || (m > 2 && y2 > 2 && y2 < m - 1)) puts("3");
				else if((n == 3 && x2 == 2) || (m == 3 && y2 == 2)) puts("1");
				else puts("2");
			} else puts("2");
		} else if((x2 <= 2 || x2 >= n - 1) && (y2 <= 2 || y2 >= m - 1)) {
			if(std::abs(x1 - x2) == 1 && std::abs(y1 - y2) == 1) {
				if(((x2 <= 2 && x1 == x2 + 1 && x2 < n - 1) || (x2 >= n - 1 && x1 == x2 - 1 && x2 > 2)) && ((y2 <= 2 && y1 == y2 + 1 && y2 < m - 1) || (y2 >= m - 1 && y1 == y2 - 1 && y2 > 2)))
					puts("3");
				else puts("2");
			} else puts("2");
		} else puts("3");
	}
	return 0;
}