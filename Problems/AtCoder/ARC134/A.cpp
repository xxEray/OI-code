#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;

LL a[N];
int n;
LL L, W;

LL calc(LL x) { return (x + W - 1) / W; }

int main() {
	scanf("%d%lld%lld", &n, &L, &W);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	LL cnt = 0;
	a[0] = -W, a[n + 1] = L;
	for(int i = 1; i <= n + 1; i++) cnt += std::max(calc(a[i] - (a[i - 1] + W)), 0LL);
	printf("%lld\n", cnt);
	return 0;
}