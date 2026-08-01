#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long long LL;

const double eps = 1e-12;
const int MAXLOG = 23;

// LL pow2[MAXLOG];
// #define log2(x) ((int)(std::upper_bound(pow2, pow2 + MAXLOG, (x)) - pow2 - 1))
#define log_(n, k) ((k) == 1 ? -1 : (int)(log(n) / log(k) + eps) + 1)

int main() {
	// for(int i = 0; i < MAXLOG; i++) pow2[i] = (1 << i);
	// for(int i = 1; i <= 20; i++) printf("log 2 %d = %d\n", i, log2(i));
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++) {
		LL x, y;
		scanf("%lld%lld", &x, &y);
		int cnt = 0;
		// printf("log %lld %lld = %d\n", x, y, log_(x, y));
		while(y == 1 || log_(x, y) >= log_(x, y + 1) + 1) y++, cnt++;
		// printf("log %lld %lld = %d\n", x, y, log_(x, y));
		printf("%d\n", cnt + log_(x, y));
	}
	return 0;
}