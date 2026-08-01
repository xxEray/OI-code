#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 100 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL a[N], b[N], c[N], mn[N], mx[N];
int n;

LL f[N][N * N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
		for(int i = 1; i <= n; i++) if(a[i] < b[i]) std::swap(a[i], b[i]);
		for(int i = 1; i <= n; i++) c[i] = c[i - 1] + a[i] + b[i], mn[i] = mn[i - 1] + b[i], mx[i] = mx[i - 1] + a[i];
		LL ans = 0;
		for(int i = 1; i <= n; i++) for(int j = 1; j < i; j++) ans += a[i] * a[i] + a[j] * a[j] + b[i] * b[i] + b[j] * b[j];
		// for(int i = 1; i <= n; i++) for(int j = 1; j < i; j++) ans += 2 * b[i] * (a[j] + b[j]);
		memset(f, 0x3f, sizeof(f));
		f[0][0] = 0;
		for(int i = 1; i <= n; i++) for(LL j = mn[i]; j <= mx[i]; j++) {
			if(j >= a[i]) f[i][j] = std::min(f[i][j], f[i - 1][j - a[i]] + a[i] * (j - a[i]) + b[i] * (c[i] - j - b[i]));
			if(j >= b[i]) f[i][j] = std::min(f[i][j], f[i - 1][j - b[i]] + b[i] * (j - b[i]) + a[i] * (c[i] - j - a[i]));
		}
		LL ret = LLINF;
		for(LL j = mn[n]; j <= mx[n]; j++) ret = std::min(ret, f[n][j]);
		ans += 2 * ret;
		printf("%lld\n", ans);
	}
	return 0;
} /*
1
2
1 2
3 4
*/