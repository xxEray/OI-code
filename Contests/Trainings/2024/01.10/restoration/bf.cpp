#include <bits/stdc++.h>

typedef long long LL;

const int N = 3000 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
LL a[N], b[N], c[N];

LL f[N][N], g[N][N];

int bigrand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

LL min(const LL &x, const LL &y) { return x < y ? x : y; }
LL max(const LL &x, const LL &y) { return x > y ? x : y; }

int main() {
	freopen("restoration.in", "r", stdin);
	freopen("restoration.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	for(int i = 0; i <= n; i++) scanf("%lld", &c[i]);
	// srand(time(0));
	// for(int i = 2; i <= n; i++) a[i] = bigrand(0, 4);
	// for(int i = 1; i <= n; i++) b[i] = bigrand(0, 20);
	// for(int i = 0; i <= n; i++) c[i] = bigrand(0, 20);
	// for(int i = 2; i <= n; i++) printf("%lld ", a[i]);
	// puts("");
	// for(int i = 1; i <= n; i++) printf("%lld ", b[i]);
	// puts("");
	// for(int i = 0; i <= n; i++) printf("%lld ", c[i]);
	// puts("");
	for(int i = 1; i <= n + 1; i++) a[i] += a[i - 1];
	// printf("a: "); for(int i = 1; i <= n; i++) printf("%lld ", a[i]); puts("");
	// for(int i = 0; i <= n + 1; i++) for(int j = 0; j <= n + 1; j++) f[i][j] = g[i][j] = LLINF;
	for(int i = 0; i <= n; i++) f[i][i + 1] = b[i] + c[i], g[i + 1][i] = b[i + 1] + c[i];
	for(int len = 1; len <= n; len++)
		for(int i = 1; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			LL v = LLINF, w = LLINF;
			for(int k = i; k <= j; k++) {
				v = std::min(v, std::max(g[i][k - 1], f[j][k + 1]) + a[k]);
				w = std::min(w, std::max(g[i][k - 1], f[j][k + 1]) - a[k]);
			}
			f[j][i] = v + b[i - 1] - a[i - 1], g[i][j] = w + b[j + 1] + a[j + 1];
		}
	// for(int i = 1; i <= n; i++)
	// 	for(int j = i; j <= n; j++)
	// 		printf("[%d, %d]: f=%lld, g=%lld\n", i, j, f[i][j], g[i][j]);
	printf("%lld\n", f[n][1]);
	return 0;
} /*
3
1 1
3 8 2
7 1 2 12
*/