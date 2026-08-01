#include <cstdio>
#include <algorithm>

int main() {
	int a, b, c, x;
	scanf("%d%d%d%d", &a, &b, &c, &x);
	if(x <= a) puts("1");
	else if(x > b) puts("0");
	else printf("%.15lf\n", (double)c / (b - a));
	return 0;
}