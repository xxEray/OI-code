#include <cstdio>
#include <algorithm>

int main() {
	int n;
	scanf("%d", &n);
	while(n % 4 != 2) n++;
	printf("%d\n", n);
	return 0;
}