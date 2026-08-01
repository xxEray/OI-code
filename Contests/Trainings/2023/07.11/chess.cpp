#include <bits/stdc++.h>

typedef long long LL;

const int N = 200 + 5;
const LL MOD = 998244353;

int n, m, Q;
LL pb[10];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

LL f[5][N][3 * N], g[N * 3][N * 3], h[N][N];

const int dir[9][2] = {{0, 0}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}};
void record_equation(int id, int i, int j) {
	for(int l = 1; l <= 2 * m + n - 1; l++) g[id][l] = f[i % 5][j][l];
	for(int k = 1; k <= 8; k++) if(j + dir[k][1] >= 1 && j + dir[k][1] <= m)
		for(int l = 1; l <= 2 * m + n - 1; l++) (g[id][l] += MOD - pb[k] * f[(i + dir[k][0] + 5) % 5][j + dir[k][1]][l] % MOD) %= MOD;
	g[id][2 * m + n - 1] = (MOD - g[id][2 * m + n - 1] + 1) % MOD;
}

void gauss(int mx) {
	// for(int i = 1; i <= mx; i++) {
	// 	for(int j = 1; j <= mx; j++) printf("%lld ", g[i][j]);
	// 	printf("= %lld\n", g[i][mx + 1]);
	// }
	for(int i = 1; i <= mx; i++) {
		int id = -1;
		for(int j = i; j <= mx; j++) if(g[j][i]) { id = j; break; }
		assert(id != -1);
		for(int k = 1; k <= mx + 1; k++) std::swap(g[i][k], g[id][k]);
		LL val = inv(g[i][i]);
		for(int k = 1; k <= mx + 1; k++) (g[i][k] *= val) %= MOD;
		for(int j = 1; j <= mx; j++) if(j != i) {
			val = g[j][i];
			for(int k = 1; k <= mx + 1; k++) (g[j][k] += MOD - val * g[i][k] % MOD) %= MOD;
		}
		// puts("--------------");
		// for(int oi = 1; oi <= mx; oi++) {
		// 	for(int oj = 1; oj <= mx; oj++) printf("%lld ", g[oi][oj]);
		// 	printf("= %lld\n", g[oi][mx + 1]);
		// }
	}
}

int main() {
	scanf("%d%d", &n, &m);
	LL sum = 0;
	for(int i = 1; i <= 8; i++) scanf("%lld", &pb[i]), (sum += pb[i]) %= MOD;
	for(int i = 1; i <= 8; i++) (pb[i] *= inv(sum)) %= MOD;
	LL invp5 = inv(pb[5]);
	for(int j = 1; j <= m; j++) f[1][j][j] = 1, f[2][j][j + m] = 1;
	for(int i = 3; i <= n; i++) {
		for(int j = 1; j <= m; j++) for(int k = 1; k <= 2 * m + n - 1; k++) f[i % 5][j][k] = 0;
		f[i % 5][1][2 * m + i - 2] = 1;
		for(int j = 2; j <= m; j++) {
			for(int k = 1; k <= 2 * m + n - 1; k++) {
				(f[i % 5][j][k] += f[(i + 3) % 5][j - 1][k] * invp5 % MOD) %= MOD;
				if(j - 2 >= 1) (f[i % 5][j][k] += MOD - f[(i + 1) % 5][j - 2][k] * pb[1] % MOD * invp5 % MOD) %= MOD;
				(f[i % 5][j][k] += MOD - f[(i + 1) % 5][j][k] * pb[8] % MOD * invp5 % MOD) %= MOD;
				if(j - 3 >= 1) (f[i % 5][j][k] += MOD - f[(i + 2) % 5][j - 3][k] * pb[2] % MOD * invp5 % MOD) %= MOD;
				if(j + 1 <= m) (f[i % 5][j][k] += MOD - f[(i + 2) % 5][j + 1][k] * pb[7] % MOD * invp5 % MOD) %= MOD;
				if(j - 3 >= 1) (f[i % 5][j][k] += MOD - f[(i + 4) % 5][j - 3][k] * pb[3] % MOD * invp5 % MOD) %= MOD;
				if(j + 1 <= m) (f[i % 5][j][k] += MOD - f[(i + 4) % 5][j + 1][k] * pb[6] % MOD * invp5 % MOD) %= MOD;
				if(j - 2 >= 1) (f[i % 5][j][k] += MOD - f[i % 5][j - 2][k] * pb[4] % MOD * invp5 % MOD) %= MOD;
			}
			(f[i % 5][j][2 * m + n - 1] += MOD - invp5) %= MOD;
			// printf("(%d, %d): ", i, j); for(int k = 1; k <= 2 * m + n - 1; k++) printf("%lld ", f[i % 5][j][k]); puts("");
		}
		record_equation(2 * m + i - 2, i - 2, m);
	}
	for(int j = 1; j <= m; j++) for(int k = 1; k <= 2 * m + n - 1; k++) f[(n + 1) % 5][j][k] = 0;
	for(int j = 1; j <= m; j++) record_equation(j, n - 1, j);
	for(int j = 1; j <= m; j++) for(int k = 1; k <= 2 * m + n - 1; k++) f[(n + 2) % 5][j][k] = 0;
	for(int j = 1; j <= m; j++) record_equation(m + j, n, j);
	gauss(2 * m + n - 2);
	// for(int i = 1; i <= 2 * m + n - 2; i++) printf("%d: %lld\n", i, g[i][2 * m + n - 1]);
	for(int j = 1; j <= m; j++) h[1][j] = g[j][2 * m + n - 1], h[2][j] = g[j + m][2 * m + n - 1];
	for(int i = 3; i <= n; i++) h[i][1] = g[2 * m + i - 2][2 * m + n - 1];
	for(int i = 3; i <= n; i++)
		for(int j = 2; j <= m; j++) {
			(h[i][j] += h[i - 2][j - 1] * invp5 % MOD) %= MOD;
			if(i - 4 >= 1 && j - 2 >= 1) (h[i][j] += MOD - h[i - 4][j - 2] * pb[1] % MOD * invp5 % MOD) %= MOD;
			if(i - 4 >= 1) (h[i][j] += MOD - h[i - 4][j] * pb[8] % MOD * invp5 % MOD) %= MOD;
			if(i - 3 >= 1 && j - 3 >= 1) (h[i][j] += MOD - h[i - 3][j - 3] * pb[2] % MOD * invp5 % MOD) %= MOD;
			if(i - 3 >= 1 && j + 1 <= m) (h[i][j] += MOD - h[i - 3][j + 1] * pb[7] % MOD * invp5 % MOD) %= MOD;
			if(j - 3 >= 1) (h[i][j] += MOD - h[i - 1][j - 3] * pb[3] % MOD * invp5 % MOD) %= MOD;
			if(j + 1 <= m) (h[i][j] += MOD - h[i - 1][j + 1] * pb[6] % MOD * invp5 % MOD) %= MOD;
			if(j - 2 >= 1) (h[i][j] += MOD - h[i][j - 2] * pb[4] % MOD * invp5 % MOD) %= MOD;
			(h[i][j] += MOD - invp5) %= MOD;
		}
	scanf("%d", &Q);
	while(Q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%lld\n", h[x][y]);
	}
	return 0;
} /*
5 4
1 1 1 1 1 1 1 1
1
1 1
*/