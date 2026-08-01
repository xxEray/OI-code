#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
LL a[N];

LL f[N][65];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		f[1][0] = 0, f[1][1] = a[1];
		for(int j = 2; j <= 60; j++) f[1][j] = LLINF;
		for(int i = 2; i <= n; i++)
			for(int j = 0; j <= 60; j++) {
				f[i][j] = f[i - 1][j];
				if(j && f[i - 1][j - 1] <= a[i])
					f[i][j] = std::min(f[i][j], f[i - 1][j - 1] + a[i]);
				// if(f[i][j] < LLINF) printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
			}
		int ans = 0;
		for(int j = 1; j <= 60; j++) if(f[n][j] < LLINF) ans = j;
		printf("%d\n", ans);
	}
	return 0;
}