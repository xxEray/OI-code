#include <cstdio>
#include <algorithm>

const int N = 100 + 5;

int a[N];
int n, x;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &x);
		for(int i = 1; i <= 2 * n; i++) scanf("%d", &a[i]);
		std::sort(a + 1, a + 2 * n + 1);
		bool flag = true;
		for(int i = 1; i <= n; i++) flag &= (a[i + n] - a[i] >= x);
		puts(flag ? "YES" : "NO");
	}
	return 0;
}