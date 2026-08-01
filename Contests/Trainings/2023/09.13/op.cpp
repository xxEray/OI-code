#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

int K, n;

LL f[12][N];

int main() {
#ifndef DEBUG
	freopen("op.in", "r", stdin);
	freopen("op.out", "w", stdout);
#endif
	scanf("%d%d", &K, &n);
	f[0][1] = 1;
	for(int j = 0; j <= 10; j++) for(int i = 1; i <= n; i++) f[j][i] += (j && i % K == 0 ? f[j - 1][i / K] : 0) + f[j][i - 1];
	for(int i = 0, tmp = n; i <= 10 && tmp; i++) {
		LL sum = 0;
		for(int j = 1; j <= n; j++) sum += f[i][j];
		printf("%lld\n", sum);
		tmp /= K;
	}
	return 0;
}