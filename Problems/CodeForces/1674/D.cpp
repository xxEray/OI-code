#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int a[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1 + (n & 1); i + 1 <= n; i += 2) if(a[i] > a[i + 1]) std::swap(a[i], a[i + 1]);
		puts(std::is_sorted(a + 1, a + n + 1) ? "YES" : "NO");
	}
	return 0;
} /*
5
1 1 1 2 1
*/