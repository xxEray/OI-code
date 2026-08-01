#include <cstdio>
#include <algorithm>

int f(int l, int r) {
	if(l == r) return 1;
	if(l + 1 == r) return 3;
	int b = l + (r - l) / 3, c = (b + r) / 2;
	return f(l, b) + f(b + 1, c) + f(c + 1, r) + 1;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%*d");
		printf("%d\n", f(1, n));
	}
	return 0;
}