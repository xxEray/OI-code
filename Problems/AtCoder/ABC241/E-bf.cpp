#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

LL a[N];
int n; LL m;

int main() {
	scanf("%d%lld", &n, &m);
	for(int i = 0; i < n; i++) scanf("%lld", &a[i]);
	LL sum = 0;
	while(m--) printf("%lld ", a[sum % n]), sum += a[sum % n];
	printf("\n%lld\n", sum);
	return 0;
} /*
5 30
1 3 2 4 5
*/