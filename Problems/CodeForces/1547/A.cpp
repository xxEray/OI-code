#include <cstdio>
#include <algorithm>

struct Point { int x, y; } a, b, c;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d%d%d%d", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y);
		int dis = std::abs(a.x - b.x) + std::abs(a.y - b.y);
		if((a.x == b.x && a.x == c.x && ((a.y <= c.y && c.y <= b.y) || (b.y <= c.y && c.y <= a.y))) || 
		   (a.y == b.y && a.y == c.y && ((a.x <= c.x && c.x <= b.x) || (b.x <= c.x && c.x <= a.x))))
			printf("%d\n", dis + 2);
		else printf("%d\n", dis);
	}
	return 0;
}