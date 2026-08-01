#include <bits/stdc++.h>

typedef long long LL;

const int N = 10;
const int MAXQ = 10;
const int V = 2e9;
const int V2 = 5e7;

LL rand(LL l, LL r) { return ((LL)rand() << 30 | rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	int n = N, Q = MAXQ;
	printf("%d %d\n", n, Q);
	for(int i = 1; i <= n; i++) printf("%lld ", rand(-V, V));
	puts("");
	while(Q--) {
		int t = rand(1, 2);
		if(t == 1) printf("1 %lld\n", rand(-V2, V2));
		else {
			int l = rand(1, n), r = rand(1, n);
			if(l > r) std::swap(l, r);
			printf("2 %d %d\n", l, r);
		}
	}
	return 0;
}
