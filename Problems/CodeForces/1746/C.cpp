#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int n;
int a[N], p[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), p[a[i]] = i;
		for(int i = 1; i <= n; i++) printf("%d ", p[i] == n ? 1 : p[i] + 1);
		puts("");
	}
	return 0;
}