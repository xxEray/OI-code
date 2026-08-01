#include <cstdio>
#include <algorithm>

const int N = 100 + 5;

int a[N], sum[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum[i] = sum[i - 1] + (a[i] == 0) + 1;
		int ans = 0;
		for(int i = 1; i <= n; i++) for(int j = i; j <= n; j++) ans += sum[j] - sum[i - 1];
		printf("%d\n", ans);
	}
	return 0;
}