#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>

const double eps = 1e-8;

double a, b, c, v;

#define zero(x) (-eps <= (x) && (x) <= eps) // x == 0
#define less(x, y) ((x) - (y) <= eps) // x <= y

double dfs(double, double, double);

double solve(double x, double y, double z, int ind) {
	if(ind == 1) std::swap(x, y);
	double a, b, c;
	if(less(x, v)) {
		if(!zero(y)) a = 0, b = y + x / 2, c = z + x / 2;
		else a = 0, b = 0, c = z + x;
	} else {
		if(!zero(y)) a = x - v, b = y + v / 2, c = z + v / 2;
		else a = x - v, b = 0, c = z + v;
	}
	if(ind == 1) std::swap(a, b);
	return dfs(a, b, c);
}

double dfs(double x, double y, double z) {
	double ex = 0;
	if(!zero(x)) ex += x * (solve(x, y, z, 0) + 1); // choose x
	if(!zero(y)) ex += y * (solve(x, y, z, 1) + 1); // choose y
	ex += z * 1; // choose z, only one chance
	return ex;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%lf%lf%lf%lf", &a, &b, &c, &v);;
		printf("%.8lf\n", dfs(a, b, c));
	}
	return 0;
} /*
1
0.2 0.2 0.6 0.2

> dfs(0.20, 0.20, 0.60)
	> dfs(0.00, 0.30, 0.70)
		> dfs(0.00, 0.20, 0.80)
			> dfs(0.00, 0.00, 1.00)
			< dfs(0.00, 0.00, 1.00) -> 1.00
		< dfs(0.00, 0.20, 0.80) -> 1.20
	< dfs(0.00, 0.30, 0.70) -> 1.36
	> dfs(0.30, 0.00, 0.70)
		> dfs(0.20, 0.00, 0.80)
			> dfs(0.00, 0.00, 1.00)
			< dfs(0.00, 0.00, 1.00) -> 1.00
		< dfs(0.20, 0.00, 0.80) -> 1.20
	< dfs(0.30, 0.00, 0.70) -> 1.36
< dfs(0.20, 0.20, 0.60) -> 1.54
*/