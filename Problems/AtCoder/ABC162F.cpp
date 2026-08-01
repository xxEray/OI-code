#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

LL a[N];
int n;

LL f[N], sum[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	sum[1] = a[1];
	for(int i = 3; i <= n; i++) if(i & 1) sum[i] = sum[i - 2] + a[i];
	for(int i = 2; i <= n; i++)
		if(i & 1) f[i] = std::max(f[i - 1], f[i - 2] + a[i]);
		else f[i] = std::max(sum[i - 1], f[i - 2] + a[i]);
	printf("%lld\n", f[n]);
	return 0;
}