#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long long LL;

const double eps = 1e-6;

const int N = 1e3 + 5;

int n;
LL P;
double pro;

LL C[N][4];

LL calc(int x) {
	LL p = 0;
	p += C[x][3] * 10000;
	p += C[x][2] * C[n - x][1] * 10000;
	p += C[x][1] * C[n - x][2] * 5000;
	// p += (LL)C[n - x][3] * 0;
	return p;
}

int main() {
	scanf("%d%lf", &n, &pro);
	P = round(pro * 10000);
	C[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= 3; j++) C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	}
	int l = 0, r = n;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(calc(mid) >= P * C[n][3]) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}