#include <cstdio>
#include <algorithm>

int P;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &P);
		printf("%d %d\n", 2, P - 1);
	}
	return 0;
}