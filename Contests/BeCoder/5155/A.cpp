#include <bits/stdc++.h>

typedef long long LL;

const int N = 500 + 5;
const LL MOD = 998244353;

int n, m;
int al[N], ar[N], bl[N], br[N];

template<typename T, int L, int R>
struct Array {
	T a[R - L + 1];
	T &operator[](int x) { return a[x - L]; }
	const T &operator[](int x) const { return a[x - L]; }
};
Array<LL, -N, N> f[2][N], g[2][N];

LL sum(int idx1, int idx2, int l, int r, int ll, int rr) {
	l = std::max(l, ll);
	r = std::min(r, rr);
	if(l > r) return 0;
	return (g[idx1][idx2][r] - g[idx1][idx2][l - 1] + MOD) % MOD;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d%d", &al[i], &ar[i]);
	for(int i = 1; i <= m; i++) scanf("%d%d", &bl[i], &br[i]);
	for(int i = 0; i <= n; i++) {
		memset(f[i & 1], 0, sizeof(f[i & 1])), memset(g[i & 1], 0, sizeof(g[i & 1]));
		for(int j = 0; j <= m; j++) for(int k = -500; k <= 500; k++) {
			if(i == 0 && j == 0 && k == 0) (f[i & 1][j][k] += 1) %= MOD;
			if(i) (f[i & 1][j][k] += sum(~i & 1, j, k - ar[i], k - al[i], -500, 0)) %= MOD;
			if(j) (f[i & 1][j][k] += sum(i & 1, j - 1, k + bl[j], k + br[j], 1, 500)) %= MOD;
			g[i & 1][j][k] = (g[i & 1][j][k - 1] + f[i & 1][j][k]) % MOD;
		}
		if(i) {
			for(int j = 1; j <= m; j++) printf("%lld ", f[i & 1][j][0]);
			puts("");
		}
	}
	return 0;
} /*
2 3
1 2
2 3
1 4
2 2
1 3
*/