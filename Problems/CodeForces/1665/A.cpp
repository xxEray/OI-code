#include <cstdio>

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		n -= 2;
		if(n == 2) printf("1 1 ");
		else if(n & 1) printf("%d %d ", n / 2, (n + 1) / 2);
		else if(n & 2) printf("%d %d ", n / 2 - 2, n / 2 + 2);
		else printf("%d %d ", n / 2 - 1, n / 2 + 1);
		puts("1 1");
	}
	return 0;
}