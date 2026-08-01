#include <cstdio>
#include <algorithm>

const int N = 20 + 5;
const int S = (1 << 20) + 5;

int n, m;
int msk[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) msk[i] = 0;
		for(int i = 1; i <= m; i++) { int x, y; scanf("%d%d", &x, &y); msk[x] |= 1 << (y - 1); }
		int U = (1 << n) - 1;
		int ans = 0;
		for(int s = 0; s <= U; s++) {
			int all = U;
			for(int i = 1; i <= n; i++) if(s >> (i - 1) & 1) all &= msk[i];
			ans = std::max(ans, __builtin_popcount(all) + __builtin_popcount(s));
		}
		printf("%d\n", ans);
	}
	return 0;
}