#include <bits/stdc++.h>

int rand(int l, int r) { return rand() % (r - l + 1) + l; }

int a[200005];

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int n = 500, d = rand(1, 20);
	printf("%d %d\n", n, d);
	for(int i = 2; i <= n; i++) printf("%d %d\n", rand(1, i - 1), i);
	for(int i = 1; i <= n; i++) a[i] = i;
	std::random_shuffle(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) printf("%d ", a[i]);
	puts("");
	return 0;
}
