#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int a[N], b[N];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);
	std::sort(a + 1, a + n + 1);
	std::sort(b + 1, b + n + 1);
	int l = ((n & 1) ? a[(n + 1) / 2] : a[n / 2] + a[n / 2 + 1]);
	int r = ((n & 1) ? b[(n + 1) / 2] : b[n / 2] + b[n / 2 + 1]);
	printf("%d\n", r - l + 1);
	return 0;
}