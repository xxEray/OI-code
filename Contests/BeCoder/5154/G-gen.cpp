#include "testlib.h"
#include <bits/stdc++.h>

const int V = 1e9;

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	freopen("in.txt", "w", stdout);
	int n = 5e5, m = 5e5;
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i++) printf("%d %d\n", rnd.next(1, V), rnd.next(1, V));
	while(m--) {
		int t = rnd.next(1, 2);
		if(t == 1) printf("1 %d %d %d\n", rnd.next(1, n), rnd.next(1, V), rnd.next(1, V));
		else {
			int l = rnd.next(1, n), r = rnd.next(1, n);
			if(l > r) std::swap(l, r);
			printf("2 %d %d %d\n", rnd.next(1, V), l, r);
		}
	}
	return 0;
}