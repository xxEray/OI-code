#include <cstdio>
#include <algorithm>

const int N = 10 + 5;

char a[N];
int x, y;

int main() {
	scanf("%s%d%d", a + 1, &x, &y);
	std::swap(a[x], a[y]);
	printf("%s\n", a + 1);
	return 0;
}