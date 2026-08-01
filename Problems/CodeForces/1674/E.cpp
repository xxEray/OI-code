#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int a[N];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int mn = INF, sc = INF;
	int ans = INF;
	for(int i = 1; i <= n; i++)
		if(a[i] <= mn) sc = mn, mn = a[i];
		else if(a[i] <= sc) sc = a[i];
	ans = std::min(ans, (mn + 1) / 2 + (sc + 1) / 2);
	for(int i = 2; i <= n; i++) {
		int x = a[i - 1], y = a[i];
		int xa = std::max((2 * x - y + 2) / 3, 0);
		int ya = std::max((y - xa + 1) / 2, 0);
		ans = std::min(ans, xa + ya);
	}
	for(int i = 2; i <= n; i++) {
		int x = a[i], y = a[i - 1];
		int xa = std::max((2 * x - y + 2) / 3, 0);
		int ya = std::max((y - xa + 1) / 2, 0);
		ans = std::min(ans, xa + ya);
	}
	for(int i = 2; i < n; i++) {
		int x = a[i - 1], y = a[i + 1];
		int ret = std::min(x, y);
		x -= ret, y -= ret;
		if(x > 0) ret += (x + 1) / 2;
		if(y > 0) ret += (y + 1) / 2;
		ans = std::min(ans, ret);
	}
	printf("%d\n", ans);
	return 0;
}