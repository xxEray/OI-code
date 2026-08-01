#include <cstdio>
#include <algorithm>

const int N = 100 + 5;

int n, m, K;
int a[N * N];

int b[N][N];

int main() {
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= K; i++) scanf("%d", &a[i]);
	int x = 1, y = 1, c = 1;
	while(x <= n) {
		while(c <= K && a[c] == 0) c++;
		a[c]--, b[x][y] = c;
		y += (x & 1) ? 1 : -1;
		if(y < 1) x++, y = 1;
		if(y > m) x++, y = m;
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) printf("%d ", b[i][j]);
		puts("");
	}
	return 0;
}