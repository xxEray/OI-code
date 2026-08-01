#include <bits/stdc++.h>

typedef long long LL;

const int N = 750 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
int a[N];

LL f[N][N], sum[N];

int main() {
	// freopen("desire.in", "r", stdin);
	// freopen("desire.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
	for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) f[i][j] = LLINF;
	f[1][0] = 0;
	for(int s = 0; s <= n; s++)
		for(int i = 0; i <= s; i++) {
			int j = s - i;
			for(int k = 0; k <= n - s; k++) {
				LL v = f[s][k] + sum[n - i];
				f[s + k][j] = std::min(f[s + k][j], v);
			}
		}
	// for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) if(f[i][j] < LLINF) printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
	printf("%lld\n", f[n][0]);
	return 0;
}