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
		LL sum = 0;
		for(int i = 1; i <= n; i++) sum += a[i];
		printf("%lld\n", std::abs(sum));
	}
	return 0;
}