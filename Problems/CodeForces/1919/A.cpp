#include <bits/stdc++.h>

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int x, y;
		scanf("%d%d", &x, &y);
		if((x + y) & 1) puts("Alice");
		else puts("Bob");
	}
	return 0;
}