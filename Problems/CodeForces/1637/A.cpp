#include <cstdio>
#include <algorithm>

const int N = 1e4 + 5;

int a[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		puts(std::is_sorted(a + 1, a + n + 1) ? "NO" : "YES");
	}
	return 0;
}