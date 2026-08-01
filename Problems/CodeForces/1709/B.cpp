#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;

int a[N];
int n, m;

LL f[N], g[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 2; i <= n; i++) f[i] = std::max(a[i - 1] - a[i], 0);
	for(int i = 2; i <= n; i++) f[i] += f[i - 1];
	for(int i = 1; i < n; i++) g[i] = std::max(a[i + 1] - a[i], 0);
	for(int i = n - 1; i >= 1; i--) g[i] += g[i + 1];
	while(m--) {
		int l, r;
		scanf("%d%d", &l, &r);
		if(l < r) printf("%lld\n", f[r] - f[l]);
		else if(l == r) puts("0");
		else printf("%lld\n", g[r] - g[l]);
	}
	return 0;
}