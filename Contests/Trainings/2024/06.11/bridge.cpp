#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e4 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, c;
LL a[N];

LL pre[N];
int m;
LL f[N][N];

int main() {
#ifndef DEBUG
	freopen("bridge.in", "r", stdin);
	freopen("bridge.out", "w", stdout);
#endif
	scanf("%d%d", &n, &c);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];
	if(c == 1) { printf("%lld\n", a[1]); return 0; }
	m = (n - 1 + (c - 1) - 1) / (c - 1) - 1;
	fprintf(stderr, "m = %d\n", m);
	for(int i = 0; i <= m + 2; i++) for(int j = 0; j <= m; j++) f[i][j] = LLINF;
	f[0][0] = 0;
	for(int i = 0; i <= m + 1; i++)
		for(int j = 0; j <= m + 1; j++) if(f[i][j] < LLINF) {
			int pos = n - (c * i - j);
			f[i + 1][j] = std::min(f[i + 1][j], f[i][j] + (pos >= 1 ? a[pos] : 0));
			if(j + c <= m) f[i + 1][j + c] = std::min(f[i + 1][j + c], f[i][j] + pre[c] + a[c]);
			for(int k = 1; k < c && j + k <= m; k++)
				if(k < pos - c + 1)
					f[i + 1][j + k] = std::min(f[i + 1][j + k], f[i][j] + pre[k] + a[pos]);
		}
	for(int i = 1; i <= n; i++) for(int j = 0; j <= m; j++)
		if(f[i][j] <= LLINF / 2) printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
	LL ans = LLINF;
	for(int i = m + 1; i <= n; i++) ans = std::min(ans, f[i][m]);
	printf("%lld\n", ans);
	return 0;
} /*
5 2
1 4 13 18 20

*/