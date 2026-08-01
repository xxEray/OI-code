#include <bits/stdc++.h>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, K;
int a[N];

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
int mod(int x) { return (x % n + n) % n; }

int g[N][20], f[N][20];

int main() {
#ifndef DEBUG
	freopen("redstone.in", "r", stdin);
	freopen("redstone.out", "w", stdout);
#endif
	scanf("%d%d", &n, &K);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	int d = gcd(n, K);
	memset(g, 0x3f, sizeof(g));
	for(int i = 0; i < d; i++) for(int v = 0; v < 16; v++) {
		int val = v, sum = v, ret = std::min(v, 16 - v);
		for(int j = mod(i + K); j != i; j = mod(j + K)) {
			val = (val + a[j] - a[mod(j - 1)] + 16) % 16, ret += std::min(val, 16 - val);
			if(j < K) (sum += val) %= 16;
		}
		val = (val + a[i] - a[mod(i - 1)] + 16) % 16;
		if(val != v) { puts("-1"); return 0; }
		// printf("i = %d, sum = %d, ret = %d\n", i, sum, ret);
		g[i][sum] = std::min(g[i][sum], ret);
	}
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for(int i = 0; i < d; i++) for(int j = 0; j < 16; j++) for(int v = 0; v < 16; v++)
		f[i + 1][j] = std::min(f[i + 1][j], f[i][(j - v + 16) % 16] + g[i][v]);
	printf("%d\n", f[d][a[K - 1]]);
	return 0;
}