#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const int MAXS = (1 << 20) + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

LL L, K;
int n, R;
LL a[3 * N];

LL f[MAXS][23];
LL g[N][23];

int main() {
	scanf("%lld%d%d%lld", &L, &R, &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= 2 * n; i++) a[i + n] = a[i] + L;
	for(int i = 0; i <= n; i++) for(int j = 1; j < R; j++) {
		LL d = L / R * j;
		int k = std::lower_bound(a + i + 1, a + i + n + 1, a[i] + d) - a;
		int l = k, r = k + n;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(std::min(a[mid] - a[i], L - (a[mid] - a[i])) <= (a[mid] - a[i] - d) * K) r = mid;
			else l = mid + 1;
		}
		g[i][j] = (a[l] - a[i] - d) * K;
		// printf("g[%d][%d] = %d\n", i, j, g[i][j]);
	}
	int U = (1 << R) - 1;
	for(int s = 0; s <= U; s++) for(int i = 0; i < R; i++) f[s][i] = LLINF;
	f[1][0] = 0;
	for(int s = 0; s <= U; s++) for(int i = 0; i < R; i++) if(s >> i & 1) {
		if(f[s][i] >= LLINF / 2) continue;
		// printf("f[%d][%d] = %d\n", s, i, f[s][i]);
		int now = std::lower_bound(a, a + n + 1, (f[s][i] / K + i * (L / R)) % L) - a;
		assert(a[now] == (f[s][i] / K + i * (L / R)) % L);
		for(int j = 0; j < R; j++) if(~s >> j & 1) {
			LL d = j - i;
			if(d < 0) d += R;
			f[s | (1 << j)][j] = std::min(f[s | (1 << j)][j], f[s][i] + g[now][d]);
		}
	}
	LL ans = LLINF;
	for(int i = 0; i < R; i++) ans = std::min(ans, f[U][i]);
	printf("%lld\n", ans);
	return 0;
} /*
32 4 4 2
23 12 5 11
*/