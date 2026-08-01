#include <bits/stdc++.h>

typedef long long LL;

const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;
const int N = 1e5 + 5;
const int SQRTN = 320;

int n, K;
struct Node { int w, s, p; } a[N];

LL f[2][SQRTN][SQRTN];

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].w, &a[i].s, &a[i].p);
	if(2 * K > n) { puts("-1"); return 0; }
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.w == y.w ? (x.p ^ 1) > (y.p ^ 1) : x.w < y.w; });
	// printf("a:\n");
	// for(int i = 1; i <= n; i++) printf("%d %d %d\n", a[i].w, a[i].s, a[i].p);
	for(int i = 0; i <= K; i++) for(int j = 0; j <= K; j++) f[0][i][j] = LLINF;
	f[0][0][0] = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= K; j++) for(int k = 0; k <= K; k++) f[i & 1][j][k] = LLINF;
		for(int j = 0; j <= K; j++) for(int k = 0; k <= j; k++) {
			f[i & 1][j][k] = f[~i & 1][j][k];
			if((a[i].p == 2 || a[i].p == 3) && j) f[i & 1][j][k] = std::min(f[i & 1][j][k], f[~i & 1][j - 1][k] + a[i].s);
			if((a[i].p == 1 || a[i].p == 3) && k) f[i & 1][j][k] = std::min(f[i & 1][j][k], f[~i & 1][j][k - 1] + a[i].s);
		}
		// printf("%d:\n", i);
		// for(int j = 0; j <= K; j++) for(int k = 0; k <= K; k++) if(f[i & 1][j][k] < LLINF) printf("[%d][%d] = %lld\n", j, k, f[i & 1][j][k]);
	}
	printf("%lld\n", f[n & 1][K][K] == LLINF ? -1LL : f[n & 1][K][K]);
	return 0;
} /*
6 2
20 6 1
6 7 2
4 8 3
3 10 2
8 5 3
4 3 1
*/