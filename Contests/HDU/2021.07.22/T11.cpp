#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = (1 << 19) + 1;
const LL MOD = 998244353;
const LL INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

LL a[N][2];
int n;

LL f[N][2][2];
LL ans[N];

LL mod(LL x) { return (x % MOD + MOD) % MOD; } // 负数取模

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		// for(int i = 0; i < N; i++)
		// 	for(int j = 0; j <= 1; j++)
		// 		f[i][j][0] = INF, f[i][j][1] = -INF;
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%lld", &a[i][0]);
		for(int i = 0; i < n; i++) scanf("%lld", &a[i][1]);
		for(int j = 0; j <= 1; j++)
			for(int i = n - 1; i >= 0; i--) {
				f[i][j][0] = f[i][j][1] = a[i][j];
				for(int k = 0; k < 20; k++) {
					if((i | (1 << k)) >= n) break;
					f[i][j][0] = std::min(f[i][j][0], f[i | (1 << k)][j][0]);
					f[i][j][1] = std::max(f[i][j][1], f[i | (1 << k)][j][1]);
				}
			}
		for(int i = 0; i < n; i++)
			ans[i] = std::max({f[i][0][0] * f[i][1][0], f[i][0][0] * f[i][1][1], f[i][0][1] * f[i][1][0], f[i][0][1] * f[i][1][1]});
		LL answ = mod(ans[n - 1]);
		for(int i = n - 2; i >= 0; i--) ans[i] = std::max(ans[i], ans[i + 1]), (answ += mod(ans[i])) %= MOD;
		printf("%lld\n", answ);
	}
	return 0;
}