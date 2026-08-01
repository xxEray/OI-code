#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 100 + 5;
const LL MOD = 998244353;

int n,  m, K;
int a[N];

LL f[N * N][N];
LL solve1() { // p >= K
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	LL ans = 0;
	for(int i = 1, i_ = 0; i <= n; i++) {
		while(i_ < i && a[i] - a[i_ + 1] > m) {
			i_++;
			for(int j = a[i_]; j <= 10000; j++) for(int k = 1; k <= n; k++) (f[j][k] += MOD - f[j - a[i_]][k - 1]) %= MOD;
			// puts(">>");
		}
		for(int k = std::max(K - (n - i), 0); k < i; k++)
			for(int j = std::max(k * a[i] - m * K, 0); j <= k * a[i]; j++)
				(ans += f[j][k]) %= MOD;
		// printf("> %lld\n", ans);
		for(int j = 10000; j >= a[i]; j--) for(int k = n; k >= 1; k--) (f[j][k] += f[j - a[i]][k - 1]) %= MOD;
	}
	return ans + 1;
}

LL solve2() { // p < K
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	LL ans = 0;
	for(int i = n, i_ = n + 1; i >= 1; i--) {
		while(i_ > i && a[i_ - 1] - a[i] > m) {
			i_--;
			for(int j = a[i_]; j <= 10000; j++) for(int k = 1; k <= n; k++) (f[j][k] += MOD - f[j - a[i_]][k - 1]) %= MOD;
			// puts("<<");
		}
		for(int k = 0; k <= std::min(n - i, K - 2); k++)
			for(int j = 0; j <= std::min((n - i - k) * (a[i] + m) - m * std::max(K - i - k, 0), 10000); j++)
				(ans += f[j][n - i - k]) %= MOD;
		// printf("< %lld\n", ans);
		for(int j = 10000; j >= a[i]; j--) for(int k = n; k >= 1; k--) (f[j][k] += f[j - a[i]][k - 1]) %= MOD;
	}
	return ans;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &m, &K);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		std::sort(a + 1, a + n + 1);
		printf("%lld\n", (solve1() + solve2()) % MOD);
	}
	return 0;
} /*
1
10 8 4
0 3 5 6 6 7 7 7 8 8
*/