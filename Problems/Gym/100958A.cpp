#include <bits/stdc++.h>

const double eps = 1e-8;

int main() {
	double d;
	scanf("%lf", &d);
	double ans = 2 * (d / sqrt(2));
	for(int i = 1; i <= d + eps; i++) {
		double j = sqrt(d * d - i * i);
		ans = std::max(ans, i + std::max(j, 1.));
		// printf("i = %d, j = %.5f, ans = %.10f\n", i, j, ans);
	}
	printf("%.12f\n", ans);
	return 0;
}