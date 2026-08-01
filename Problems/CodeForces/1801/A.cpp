#include <cstdio>
#include <algorithm>

const int N = 500 + 5;

int n, m;
int a[N][N];

int main() {
	int cnt = 0;
	for(int i = 0; i < 128; i++) for(int j = 0; j < 128; j++) {
		a[2 * i + 0][2 * j + 0] = cnt++;
		a[2 * i + 0][2 * j + 1] = cnt++;
		a[2 * i + 1][2 * j + 0] = cnt++;
		a[2 * i + 1][2 * j + 1] = cnt++;
	}
	// for(int oi = 0; oi <= 1; oi++) for(int oj = 0; oj <= 1; oj++) for(int i = oi; i < 256; i += 2) for(int j = oj; j < 256; j += 2)
	// 	b[i][j] = a[i][j] ^ a[i + 1][j] ^ a[i][j + 1] ^ a[i + 1][j + 1];
	// for(int oi = 0; oi <= 1; oi++) for(int oj = 0; oj <= 1; oj++) for(int i = oi; i < 256; i += 2) for(int j = oj; j < 256; j += 2)
	// 	if(i < 127 && j < 127 && b[i][j] != b[i + 1][j + 1]) puts("false");
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		printf("%d\n", n * m);
		for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) printf("%d%c", a[i][j], (j == m - 1 ? '\n' : ' '));
	}
	return 0;
}