#include <bits/stdc++.h>

int a[3005];

int main() {
	freopen("cake.in", "w", stdout);
	int n = 3000;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) a[i] = rand() << 15 | rand();
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) printf("%d ", a[i]);
	puts("");
	return 0;
}