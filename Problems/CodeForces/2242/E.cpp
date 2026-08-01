#include <bits/stdc++.h>

int highbit(int x) { // return 1 << i instead of i
	for(int i = 30; i >= 0; i--) if(x >> i & 1) return 1 << i;
	return 0;
}

void print(int x, int y, int n) {
	// printf("print %d %d [%d bits]\n", x, y, n);
	assert(x && y);
	int lx = 0, ly = 0;
	for(int i = 30; i >= 0; i--) if(x >> i & 1) { lx = i + 1; break; }
	for(int i = 30; i >= 0; i--) if(y >> i & 1) { ly = i + 1; break; }
	for(int i = 0; i < n; i++) printf("%d", (x >> (lx - i % lx - 1) & 1) & (y >> (ly - i % ly - 1) & 1));
	puts("");

}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int l, r, n;
		scanf("%d%d%d", &l, &r, &n);
		if(highbit(l) == highbit(r)) {
			int diff = highbit(l ^ r);
			int prefix = l & ~(diff - 1);
			print(l, prefix | diff, n);
		} else {
			int x = highbit(r);
			if(l <= (x >> 1)) print(x >> 1, x, n);
			else print(l, x, n);
		}
	}
	return 0;
}