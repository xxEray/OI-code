#include <bits/stdc++.h>

int main() {
	int a[5] = {};
	scanf("%d%d%d", &a[0], &a[1], &a[2]);
	std::sort(a, a + 3);
	puts((a[0] == a[1] && a[1] != a[2]) || (a[1] == a[2] && a[0] != a[1]) ? "Yes" : "No");
	return 0;
}