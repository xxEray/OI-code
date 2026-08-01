#include <cstdio>
#include <algorithm>
#include <cstring>
using std::min, std::max;

typedef long long LL;

const int N = 30 + 5;

char s[N];
int n, m;

LL f[N][N][N][N * N << 1];
int kth[N][3], prev[N][3], cnt[5];

int main() {
	scanf("%s%d", s + 1, &m);
	n = strlen(s + 1);
	m = min(m, n * (n - 1) / 2);
	for(int i = 1; i <= n; i++) s[i] = (s[i] == 'K' ? 0 : (s[i] == 'E' ? 1 : 2));
	for(int i = 1; i <= n; i++) {
		prev[i][0] = prev[i - 1][0], prev[i][1] = prev[i - 1][1], prev[i][2] = prev[i - 1][2];
		prev[i][s[i]]++;
		kth[++cnt[s[i]]][s[i]] = i;
	}
	f[0][0][0][0] = 1;
	for(int i = 0; i <= cnt[0]; i++)
		for(int j = 0; j <= cnt[1]; j++)
			for(int k = 0; k <= cnt[2]; k++)
				for(int t = 0; t <= m; t++) {
					if(i < cnt[0]) f[i + 1][j][k][min(m + 1, t + max(j - prev[kth[i + 1][0]][1], 0) + max(k - prev[kth[i + 1][0]][2], 0))] += f[i][j][k][t];
					if(j < cnt[1]) f[i][j + 1][k][min(m + 1, t + max(i - prev[kth[j + 1][1]][0], 0) + max(k - prev[kth[j + 1][1]][2], 0))] += f[i][j][k][t];
					if(k < cnt[2]) f[i][j][k + 1][min(m + 1, t + max(i - prev[kth[k + 1][2]][0], 0) + max(j - prev[kth[k + 1][2]][1], 0))] += f[i][j][k][t];
				}
	// for(int i = 0; i <= cnt[0]; i++)
	// 	for(int j = 0; j <= cnt[1]; j++)
	// 		for(int k = 0; k <= cnt[2]; k++)
	// 			for(int t = 0; t <= m; t++)
	// 				printf("f[%d][%d][%d][%d] = %d\n", i, j, k, t, f[i][j][k][t]);
	LL ans = 0;
	for(int i = 0; i <= m; i++) ans += f[cnt[0]][cnt[1]][cnt[2]][i];
	printf("%lld\n", ans);
	return 0;
}