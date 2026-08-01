#include <cstdio>
#include <algorithm>

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int x, y;
		scanf("%d%d", &x, &y);
		if(x == 0 || y % x) puts("0 0");
		else printf("1 %d\n", y / x);
	}
	return 0;
}