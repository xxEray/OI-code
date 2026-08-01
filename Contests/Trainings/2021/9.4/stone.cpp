#include <cstdio>

typedef long long LL;

const int N = 1e5 + 5;

int n;
LL a[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	double ans = 0;
	for(int i = 2; i <= n; i++) ans += (double)a[i] / (a[1] + a[i]);
	printf("%.7lf\n", ans + 1);
	return 0;
}