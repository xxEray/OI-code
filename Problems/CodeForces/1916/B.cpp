#include <bits/stdc++.h>

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
int lcm(int x, int y) { return x / gcd(x, y) * y; }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int a, b;
		scanf("%d%d", &a, &b);
		int v = lcm(a, b);
		if(v == b) v *= b / a;
		printf("%d\n", v);
	}
	return 0;
}