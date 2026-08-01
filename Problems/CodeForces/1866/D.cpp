// Don't kill monsters, you dolphin!
// Authored by E-ray from team CDFLS: OPJ BLOCK

#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 1e12;

int n, m, K;
LL a[N][13];

LL f[N][25];

inline int cl(int i) { return std::max(0, i - K + 1); }
inline int cr(int i) { return std::min(i, m - K + 1); }

int main() {
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%lld", &a[j][i]);
	for(int i = 1; i <= m; i++) {
		std::sort(a[i] + 1, a[i] + n + 1, std::greater<LL>());
		for(int j = 1; j <= n; j++) a[i][j] += a[i][j - 1];
		for(int j = n + 1; j <= K; j++) a[i][j] = -LLINF;
	}
	memset(f, ~0x3f, sizeof(f));
	f[0][0 + K] = 0;
	for(int i = 0; i < m; i++)
		for(int j = cl(i); j <= cr(i); j++)
			for(int k = 0; k <= K; k++)
				if(cl(i + 1) <= j + k && j + k <= cr(i + 1))
					f[i + 1][j + k - (i + 1) + K] = std::max(f[i + 1][j + k - (i + 1) + K], f[i][j - i + K] + a[i + 1][k]);
	// for(int i = 1; i <= m; i++) for(int j = std::max(i - K, 0); j <= std::min(i + K, m); j++)
	// 	printf("f[%d][%d] = %lld\n", i, j, f[i][j + K]);
	printf("%lld\n", f[m][-(K - 1) + K]);
	return 0;
}