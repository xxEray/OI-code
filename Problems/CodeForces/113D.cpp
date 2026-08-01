#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#include <cassert>

const double eps = 1e-8;
const int N = 22 + 5;

bool G[N][N];
int n, m, A, B;

double prob[N][N], matrix[N * N][N * N];
int hash[N][N];

void gauss(int r, int c) {
	for(int i = 1; i <= r; i++) {
		for(int j = i; j <= r; j++) if(fabs(matrix[j][i]) > eps) { for(int k = 1; k <= c; k++) std::swap(matrix[i][k], matrix[j][k]); break; }
		for(int j = c; j >= i; j--) matrix[i][j] /= matrix[i][i];
		for(int j = i + 1; j <= r; j++) {
			double coe = matrix[j][i] / matrix[i][i];
			for(int k = 1; k <= c; k++) matrix[j][k] -= matrix[i][k] * coe;
		}
	}
	for(int i = r; i >= 1; i--)
		for(int j = 1; j < i; j++) {
			double coe = matrix[j][i] / matrix[i][i];
			for(int k = i; k <= c; k++) matrix[j][k] -= matrix[i][k] * coe;
		}
}

int main() {
	scanf("%d%d%d%d", &n, &m, &A, &B);
	if(A > B) std::swap(A, B);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); if(u != v) G[u][v] = G[v][u] = true; }
	for(int i = 1; i <= n; i++) {
		double p;
		scanf("%lf", &p);
		prob[i][i] = p;
		int cnt = 0;
		for(int j = 1; j <= n; j++) cnt += G[i][j];
		for(int j = 1; j <= n; j++) if(i != j) prob[i][j] = (G[i][j] ? (1 - p) / cnt : 0);
	}
	int cn = 0;
	for(int i = 1; i <= n; i++) for(int j = i; j <= n; j++) hash[j][i] = hash[i][j] = ++cn; // with optimization (1/8)
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) hash[i][j] = ++cn; // no optimization
	for(int endp = 1; endp <= n; endp++) {
		memset(matrix, 0, sizeof(matrix));
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) {
			for(int i_ = 1; i_ <= n; i_++) for(int j_ = 1; j_ <= n; j_++)
				if(i != j) matrix[hash[i][j]][hash[i_][j_]] -= prob[i][i_] * prob[j][j_];
			matrix[hash[i][j]][hash[i][j]] += 1;
			if(i == j) matrix[hash[i][j]][cn + 1] += (i == endp);
		}
		gauss(cn, cn + 1);
		printf("%.7lf\n", matrix[hash[A][B]][cn + 1]);
	}
	return 0;
}