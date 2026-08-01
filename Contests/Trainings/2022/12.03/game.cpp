#include <cstdio>
#include <algorithm>

int n, m;

int main() {
#ifndef DEBUG
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	if(n == 1) {
		for(int i = 1; i <= m; i++) scanf("%*d");
		char s[305];
		scanf("%s", s);
		long long sum = 0;
		for(int i = 0; s[i]; i++) sum = (sum * 10 + s[i] - '0') % 1000000007;
		printf("%lld\n", sum);
		return 0;
	}
	return 0;
}
