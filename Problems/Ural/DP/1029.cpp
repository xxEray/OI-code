#include <cstdio>
#include <algorithm>
typedef long long LL;

const int N = 100 + 5;
const int M = 500 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL a[N][M];
int n, m;

LL pre[N][M];
LL f[N][M];
int last[N][M];

LL sum_(int i, int stj, int edj) { return pre[i][edj] - pre[i][stj - 1]; }
LL sum(int i, int j1, int j2) { return sum_(i, std::min(j1, j2), std::max(j1, j2)); }

void print(int i, int j) {
	if(i == 0) return;
	print(i - 1, last[i][j]);
	if(last[i][j] == j) printf("%d ", j);
	else if(last[i][j] < j)
		for(int k = last[i][j]; k <= j; k++) printf("%d ", k);
	else
		for(int k = last[i][j]; k >= j; k--) printf("%d ", k);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%lld", &a[i][j]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			pre[i][j] = pre[i][j - 1] + a[i][j];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			f[i][j] = LLINF;
			for(int k = 1; k <= m; k++)
				if(f[i][j] > f[i - 1][k] + sum(i, j, k))
					f[i][j] = f[i - 1][k] + sum(i, j, k), last[i][j] = k;
		}
	int ind = 1;
	for(int i = 2; i <= m; i++) if(f[n][i] < f[n][ind]) ind = i;
	print(n, ind);
	return 0;
} /*
5 5
10 1  10 10 10
1  1  10 10 10
1  10 1  1  1
1  1  1  10 1
10 10 10 10 1
*/