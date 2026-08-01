#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

int n;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		LL sum = 0;
		for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); sum += x; }
		printf("%lld\n", (sum % n) * (n - sum % n));
	}
	return 0;
}