#include <cstdio>
#include <algorithm>

const int N = 100 + 5;

int a[N];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		int mn = *std::min_element(a + 1, a + n + 1);
		int cnt = 0;
		for(int i = 1; i <= n; i++) cnt += (a[i] == mn);
		printf("%d\n", n - cnt);
	}
	return 0;
}