#include <cstdio>
#include <algorithm>

const int N = 1e4 + 5;

double ans[N];

void prepare() {
	ans[0] = ans[1] = 0;
	double s = 0, now = 1;
	for(int k = 2; k <= 10000; k++) {
		now /= 2;
		ans[k] = ans[k - 1] + s * 2 + now;
		s += now;
	}
	// for(int k = 1; k <= 5; k++) printf("ans[%d] = %.6lf\n", k, ans[k]);
}

int main() {
	prepare();
	int T;
	scanf("%d", &T);
	while(T--) {
		int xrt, yrt, xl, yl, xr, yr;
		int k;
		scanf("%d%d%d%d%d%d%d", &k, &xrt, &yrt, &xl, &yl, &xr, &yr);
		double h = yrt - yl, w = xr - xl;
		printf("%.3lf\n", ans[k] * h * w);
	}
	return 0;
}