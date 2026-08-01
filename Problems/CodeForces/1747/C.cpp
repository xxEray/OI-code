#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;

int a[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		int mn = a[2];
		for(int i = 2; i <= n; i++) mn = std::min(mn, a[i]);
		puts(a[1] > mn ? "Alice" : "Bob");
	}
	return 0;
} /*
1 1
*/