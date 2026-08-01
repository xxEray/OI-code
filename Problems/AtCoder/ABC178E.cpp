#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int x[N], y[N];
int n;

int main() {
	std::scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int a, b;
		std::scanf("%d%d", &a, &b);
		x[i] = a + b, y[i] = a - b;
	}
	int disx = *std::max_element(x + 1, x + n + 1) - *std::min_element(x + 1, x + n + 1);
	int disy = *std::max_element(y + 1, y + n + 1) - *std::min_element(y + 1, y + n + 1);
	std::printf("%d\n", std::max(disx, disy));
	return 0;
}