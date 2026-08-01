#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 5000 + 5;

int n;
LL mod;

int a[N];
LL f[N];

int main() {
	scanf("%d%lld", &n, &mod);
	for(int i = 1; i <= (n + 1) / 2; i++) a[i] = i;
	for(int i = (n + 1) / 2 + 1; i <= n; i++) a[i] = (n + 1) / 2 - (i - (n - (n - 1) / 2));
	// printf("a: "); for(int i = 1; i <= n; i++) { printf("%d ", a[i]); } puts("");
	f[0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = a[i]; j < n; j++)
			(f[j] += f[j - a[i]]) %= mod;
	LL ans = 0;
	for(int i = 0; i <= n; i++) (ans += f[i]) %= mod;
	printf("%lld\n", ans);
	return 0;
}