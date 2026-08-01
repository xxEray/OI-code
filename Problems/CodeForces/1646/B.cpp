#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

LL a[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		std::sort(a + 1, a + n + 1);
		LL suma = a[1], sumb = 0;
		bool flag = false;
		for(int i = 2, j = n; i < j; i++, j--) {
			suma += a[i], sumb += a[j];
			flag |= suma < sumb;
		}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}