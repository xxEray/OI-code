#include <bits/stdc++.h>

typedef long long LL;

const int N = 50 + 5;

LL n_;
int m;

int power[N][N], power2[N][N];

char mp[55][200005];
int dfs(LL n, int cnt) {
	if(n == 0) return 0;
	int hn = (n <= 100000 ? n : 100000 + n_ / n);
	if(mp[cnt][hn] != -1) return mp[cnt][hn];
	int ret = power2[cnt][n % 18 + 18] - power2[cnt + 18][n % 18 + 18];
	for(int d = 2; d <= m; d++) ret += dfs(n / d, power[cnt][d] + 1) * power[cnt][n % d];
	// printf("dfs(%lld, %d) = %d\n", n, cnt, ret);
	return mp[cnt][hn] = ret % 19;
}

int main() {
	scanf("%lld%d", &n_, &m);
	// int st = clock();
	for(int i = 0; i <= 50; i++) {
		power[i][0] = power2[i][0] = 1;
		for(int j = 1; j <= 50; j++) power[i][j] = power2[i][j] = power[i][j - 1] * i % 19;
	}
	power2[0][0] = power2[19][0] = power2[38][0] = 0;
	memset(mp, -1, sizeof(mp));
	printf("%d\n", (dfs(n_, 1) + 19) % 19);
	// fprintf(stderr, "%d\n", (int)(clock() - st));
	return 0;
} /*
463 41
8150007684 47
84498 47
*/