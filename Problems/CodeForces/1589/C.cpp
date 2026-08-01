#include <cstdio>
#include <algorithm>

const int N = 100 + 5;

int a[N], b[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
		std::sort(a + 1, a + n + 1), std::sort(b + 1, b + n + 1);
		bool flag = true;
		for(int i = 1; i <= n; i++) flag &= (a[i] == b[i] || a[i] + 1 == b[i]);
		puts(flag ? "YES" : "NO");
	}
	return 0;
}