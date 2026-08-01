#include <bits/stdc++.h>

int rand(int l, int r) { return rand() % (r - l + 1) + l; }

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int n = rand(1, 10);
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) {
		int len = rand(1, 10);
		while(len--) putchar(rand('a', 'z'));
		puts("");
	}
	return 0;
}