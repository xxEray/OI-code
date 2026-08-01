#include <bits/stdc++.h>

const int N = 1000;

int a[N + 5];

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	freopen("yacolorful.in", "w", stdout);
	int n = N;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) a[i] = i;
	std::random_shuffle(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) printf("%d ", a[i]);
	puts("");
	return 0;
}