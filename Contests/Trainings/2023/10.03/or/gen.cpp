#include <bits/stdc++.h>

const int V = 20;

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int l = rand(1, V), r = rand(1, V);
	if(l > r) std::swap(l, r);
	printf("%d %d\n", l, r);
	return 0;
}