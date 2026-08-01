#include <bits/stdc++.h>

const int N = 30 + 5;
const int M = 2 * N;

int n;
int a[N];

int sum;
bool f[N][M][M * M / 2];
int last[2][N][M][M * M / 2];

bool check(int m) {
	memset(f, 0, sizeof(f));
	f[0][0][0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= 2 * m; j++)
			for(int k = 2 * m; k >= j; k--)
				for(int t = std::max(a[i] * j, k * (k - 1) / 2); t < M * M / 2; t++)
					if(f[i - 1][k - j][t - a[i] * j])
						f[i][k][t] = true, last[0][i][k][t] = i, last[1][i][k][t] = j;
	}
	// for(int i = 0; i <= 2 * m; i++) for(int j = 0; j < M * M / 2; j++) if(f[n][i][j]) printf("f[%d][%d] = true\n", i, j);
	return f[n][m][m * (m - 1) / 2];
}

int b[N], c[M][M], d[M], e[M];
void get_ans(int now, int i, int j) {
	if(now == 0) return;
	int id = last[0][now][i][j], num = last[1][now][i][j];
	b[id] += num;
	get_ans(now - 1, i - num, j - a[id] * num);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1);
	int mx = 0;
	for(int i = 1; i <= n; i++) sum += a[i], mx = std::max(mx, a[i]);
	int ans = 0;
	for(int i = std::max(n, mx + 1); i < M; i++) if(check(i)) { ans = i; break; }
	if(ans) printf("%d\n", ans);
	else { puts("=("); return 0; }
	get_ans(n, ans, ans * (ans - 1) / 2);
	// for(int i = 1; i <= n; i++) printf("%d * %d\n", b[i], a[i]);
	int m = 0;
	for(int i = 1; i <= n; i++) for(int _ = 1; _ <= b[i]; _++) e[++m] = a[i];
	assert(m == ans);
	std::sort(e + 1, e + m + 1);
	for(int i = 1; i <= m; i++) d[i] = i - 1;
	for(int i = 1; i <= m; i++) for(int j = 1; j < i; j++) c[i][j] = true;
	while(true) {
		int x;
		for(x = 1; x <= m; x++) if(d[x] < e[x]) break;
		if(x > m) break;
		while(x < m && d[x + 1] == d[x]) x++;
		int y;
		for(y = 1; y <= m; y++) if(d[y] > e[y]) break;
		assert(y <= m);
		bool flag = false;
		for(int z = 1; z <= m; z++) if(c[z][x] && c[y][z]) {
			std::swap(c[x][z], c[z][x]), std::swap(c[z][y], c[y][z]);
			d[x]++, d[y]--;
			flag = true;
			break;
		}
		if(!flag && c[y][x]) {
			std::swap(c[x][y], c[y][x]);
			d[x]++, d[y]--;
			flag = true;
			break;
		}
		assert(flag);
		// printf("d: "); for(int i = 1; i <= m; i++) printf("%d ", d[i]); puts("");
		// printf("e: "); for(int i = 1; i <= m; i++) printf("%d ", e[i]); puts("\n");
	}
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= m; j++) printf("%d", c[i][j]);
		puts("");
	}
	return 0;
}