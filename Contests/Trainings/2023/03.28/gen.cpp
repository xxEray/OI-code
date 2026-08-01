#include <bits/stdc++.h>

typedef long long LL;

LL bigrand() { return (LL)rand() << 30 | rand() << 15 | rand(); }
LL rnd(LL l, LL r) { return bigrand() % (r - l + 1) + l; }

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int n = rnd(1, 3);
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) printf("%lld ", std::max(-2000000000LL, std::min(2000000000LL, rnd(-4e9, 4e9))));
	return 0;
}