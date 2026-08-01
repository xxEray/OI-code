#include <bits/stdc++.h>

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main() {
	freopen("lycoris.in", "w", stdout);
	srand(time(0));
	int n = 10000;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) putchar(rand(0, 9) == 0 ? '?' : rand('a', 'z'));
	return 0;
}
