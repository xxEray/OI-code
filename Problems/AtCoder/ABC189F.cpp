#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;
const double eps = 1e-6;

int n, m, k;

bool turn[N];

struct Number {
	double tms, pls; // tms * x + pls (tms -> times, pls -> plus)
	Number() : tms(0), pls(0) {}
	Number(double num) : tms(0), pls(num) {}
	Number(double tms, double pls) : tms(tms), pls(pls) {}
	Number operator+(const Number &rhs) const { return Number(tms + rhs.tms, pls + rhs.pls); }
	Number operator-(const Number &rhs) const { return Number(tms - rhs.tms, pls - rhs.pls); }
	Number operator*(const double &rhs) const { return Number(tms * rhs, pls * rhs); }
	Number operator/(const double &rhs) const { return Number(tms / rhs, pls / rhs); }
};

Number f[N], pre[N];

int main() {
	std::scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= k; i++) {
		int x;
		std::scanf("%d", &x);
		turn[x] = true;
	}
	for (int i = n - 1; i >= 0; i--) {
		if (turn[i]) f[i] = Number(1, 0);
		else f[i] = (pre[i + 1] - pre[i + m + 1]) / m + Number(1);
		pre[i] = pre[i + 1] + f[i];
	}
	// std::printf("x = %lf * x + %lf\n", f[0].tms, f[0].pls);
	if (std::abs(f[0].tms - 1) <= eps) // f[0].tms == 1
		std::puts("-1");
	else
		std::printf("%.4lf\n", f[0].pls / (1 - f[0].tms)); // x = f[0].tms * x + f[0].pls => x = f[0].pls / (1 - f[0].tms)
	return 0;
}