#include <cstdio>
#include <algorithm>

const int N = 1e4 + 5;
const int M = 50 + 5;
const int INF = 0x3f3f3f3f;

char s[N];
int n, m;

int f[N][M], last[N][N];

int count(int l, int r) { return r / 10 - l / 10 + (l % 10 == 0); }

void print(int i, int j) {
	if(j) print(i - 1, j - last[i][j]);
	for(int k = i + j - last[i][j]; k <= i + j - 1; k++) printf("%d ", k);
}

int main() {
	scanf("%d%d%s", &n, &m, s + 1);
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= m; j++)
			f[i][j] = INF;
	f[0][0] = 0;
	for(int i = 1; i <= n; i++) f[i][0] = f[i - 1][0] + (i % 10 == 0 && s[i] == '1');
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			for(int k = 0; k <= j; k++) {
				int ret = f[i - 1][k] + ((i + j) % 10 == 0 && s[i] == '1') + count(i + k, i + j - 1);
				if(f[i][j] > ret) f[i][j] = ret, last[i][j] = j - k;
			}
	int ans = INF, ansid;
	for(int i = 0; i <= m; i++)
		if(f[n][i] < ans) ans = f[n][i], ansid = i;
	printf("%d\n%d ", ans, ansid);
	print(n, ansid);
	return 0;
}