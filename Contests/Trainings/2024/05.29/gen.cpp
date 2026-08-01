#include <bits/stdc++.h>

int main() {
	freopen("silksong.in", "w", stdout);
	int n = 40, m = 60;
	printf("%d %d\n", n, m);
	for(int i = 1; i <= m; i++) printf("%d %d\n", rand() % n + 1, rand() % n + 1);
	return 0;
}