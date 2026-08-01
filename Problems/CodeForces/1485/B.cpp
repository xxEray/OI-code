#include <cstdio>

typedef long long LL;

const int N = 1e5 + 5;

int a[N];
int n, m, k;

LL pre[N];

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	a[0] = 0, a[n + 1] = k + 1;
	for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i + 1] - a[i - 1] - 2;
	for(int i = 1; i <= m; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		if(l == r) printf("%d\n", k - 1);
		else printf("%lld\n", pre[r - 1] - pre[l] + k - a[r - 1] + a[l + 1] - 3);
	}
	return 0;
}