#include <cstdio>
#include <algorithm>

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n, m;
		scanf("%d%d", &n, &m);
		printf("%d\n", (n * m + 2) / 3);
	}
	return 0;
}