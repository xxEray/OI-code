#include <cstdio>
#include <algorithm>

int n;

int main() {
	scanf("%d", &n);
	printf("%d\n", 2 * n);
	int cnt = 0;
	while(n >= 4) n -= 4, cnt++;
	if(n) printf("%d", n);
	while(cnt--) putchar('4');
	return 0;
}