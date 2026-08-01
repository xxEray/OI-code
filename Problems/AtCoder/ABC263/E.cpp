#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = (1 << 18) + 5;
const int LOG_N = 18 + 3;

int n, K, Q;
LL a[N][LOG_N];

LL rf[LOG_N][N], g[LOG_N][N];

#define f(i, s, t) (rf[(i)][((t) << (i) | (s))])

int main() {
	scanf("%d", &K);
	n = 1 << K;
	for(int i = 0; i < n; i++) for(int j = 1; j <= K; j++) scanf("%lld", &a[i][j]);
	for(int i = 0; i < n; i++) for(int j = K; j >= 1; j--) a[i][j] -= a[i][j - 1];
	// for(int i = 0; i < n; i++) for(int j = 1; j <= K; j++) printf("%lld%c", a[i][j], " \n"[j == K]);
	for(int i = 0; i < n; i++) f(K, i, 0) = 0;
	for(int i = K - 1; i >= 0; i--)
		for(int j = 0; j < (1 << i); j++) {
			g[i][j] = 0;
			for(int k = 0; k < (1 << (K - i)); k++) {
				if(k >> (K - i - 1) & 1) f(i, j, k) = g[i + 1][j << 1] + f(i + 1, j << 1 | 1, k ^ (1 << (K - i - 1))) + a[(j << (K - i)) + k][K - i];
				else f(i, j, k) = f(i + 1, j << 1, k) + g[i + 1][j << 1 | 1] + a[(j << (K - i)) + k][K - i];
				g[i][j] = std::max(g[i][j], f(i, j, k));
				// printf("f[%d][%d][%d] = %lld\n", i, j, k, f(i, j, k));
			}
		}
	printf("%lld\n", g[0][0]);
	return 0;
}