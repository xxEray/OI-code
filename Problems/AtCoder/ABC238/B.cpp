#include <cstdio>
#include <algorithm>

const int N = 360 + 5;

int a[N];
int n;

int main() {
	scanf("%d", &n);
	int x = 0;
	for(int i = 1; i <= n; i++) { scanf("%d", &a[i]); x = (x + a[i]) % 360; a[i] = x; }
	std::sort(a + 1, a + n + 1);
	int ans = (360 - a[n]) % 360;
	for(int i = 1; i <= n; i++) ans = std::max(ans, a[i] - a[i - 1]);
	printf("%d\n", ans);
	return 0;
}