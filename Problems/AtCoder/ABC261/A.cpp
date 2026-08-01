#include <cstdio>
#include <algorithm>
#include <cstring>

int main() {
	int l1, r1, l2, r2;
	scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
	int l = std::max(l1, l2), r = std::min(r1, r2);
	printf("%d\n", std::max(r - l, 0));
	return 0;
}