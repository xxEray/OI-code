#include <bits/stdc++.h>

int main() {
	freopen("ape.in", "w", stdout);
	int n = 500, Q = 3e5;
	printf("%d %d\n", n, Q);
	for(int _ = 1; _ <= n + 2; _++) {
		for(int i = 1; i <= n; i++) printf("%d ", rand() % 10000 + 1);
		puts("");
	}
	while(Q--) {
		int l1 = rand() % n + 1, r1 = rand() % n + 1, l2 = rand() % n + 1, r2 = rand() % n + 1;
		if(l1 > r1) std::swap(l1, r1);
		if(l2 > r2) std::swap(l2, r2);
		printf("%d %d %d %d\n", l1, r1, l2, r2);
	}
	return 0;
}