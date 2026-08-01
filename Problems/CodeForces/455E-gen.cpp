#include <bits/stdc++.h>

int main() {
	freopen("in.txt", "w", stdout);
	int n = 30000;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) printf("%d ", rand() % 10000);
	puts("");
	int Q = 100000;
	printf("%d\n", Q);
	while(Q--) {
		int l = rand() % n + 1, r = rand() % n + 1;
		if(l > r) std::swap(l, r);
		printf("%d %d\n", l, r);
	}
	return 0;
}