#include <cstdio>
#include <algorithm>

int a[200];

int main() {
	for(int i = 0; i <= 9; i++) scanf("%d", &a[i]);
	printf("%d\n", a[a[a[0]]]);
	return 0;
}