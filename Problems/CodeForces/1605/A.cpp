#include <cstdio>
#include <algorithm>

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		printf("%d\n", std::abs(a + c - 2 * b) % 3 ? 1 : 0);
	}
	return 0;
} /*
a-2 b+1
a+2 b-1
*/