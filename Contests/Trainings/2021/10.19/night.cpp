#include <cstdio>
#include <algorithm>

const int N = 1000 + 5;
const int MAXS = 5000 + 5;

int n, m, r, c, S;

double f[N][2], g[N][2];
double ansf[MAXS], ansg[MAXS];

void DP(double F[N][2], double ansF[MAXS], int mx, int ind) {
	for(int i = 1; i <= mx; i++) F[i][0] = 1;
	ansF[0] = F[ind][0];
	for(int j = 1; j <= S; j++) {
		for(int i = 1; i <= mx; i++)
			F[i][j & 1] = (F[i + 1][(j & 1) ^ 1] + F[i - 1][(j & 1) ^ 1]) / 2;
		ansF[j] = F[ind][j & 1];
	}
}

int main() {
	scanf("%d%d%d%d%d", &n, &m, &r, &c, &S);
	++r, ++c;
	DP(f, ansf, n, r), DP(g, ansg, m, c);
	double ans = 0, C = 1;
	int div = S;
	for(int i = 0; i <= S; i++) {
		if(i) C *= (double)(S - i + 1) / i;
		// printf("C(%d, %d) = %.3lf\n", S, i, C);
		while(div && C > 1.0) C /= 2, div--;
		double C_ = C;
		for(int j = 1; j <= div; j++) C_ /= 2;
		ans += ansf[i] * ansg[S - i] * C_;
	}
	printf("%.8lf\n", ans);
	return 0;
}