#include <bits/stdc++.h>

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		double s, a;
		int t;
		scanf("%lf%lf%d", &s, &a, &t);
		double dl = 2 * a, dr = 2 * s;
		dl = 1 / dl, dr = 1 / dr;
		std::swap(dl, dr);
		double r = (dr - dl) / 2;
		double x = dl + r, y = t * 2 * r;
		double d = sqrt(x * x + y * y);
		// printf("%f %f %f %f %f %f\n", dl, dr, r, x, y, d);
		printf("%.10f\n", (1 / (d - r) - 1 / (d + r)) / 2);
	}
	return 0;
}