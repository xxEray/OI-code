#include <cstdio>
#include <algorithm>

const int N = 50 + 5;

int n, K;
int a[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &K);
		bool flag = false;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), flag |= a[i] == 1;
		puts(flag ? "YES" : "NO");
	}
	return 0;
}