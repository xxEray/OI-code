#include <bits/stdc++.h>

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int x, k;
		scanf("%d%d", &x, &k);
		int sgn = (x > 0 ? 1 : -1);
		if(std::abs(x) % k == 0) printf("2\n%d %d\n", sgn * (std::abs(x) + 1), sgn * -1);
		else printf("1\n%d\n", x);
	}
	return 0;
}