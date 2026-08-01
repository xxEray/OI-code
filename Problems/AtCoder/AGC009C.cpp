#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const LL MOD = 1e9 + 7;

int n;
LL A, B;
LL a[N];

LL f[N], presum[N];

int main() {
	scanf("%d%lld%lld", &n, &A, &B);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	if(A > B) std::swap(A, B);
	a[n + 1] = LLINF;
	f[0] = 1, presum[0] = 1;
	int last = 1, p = 0;
	for(int i = 1; i <= n + 1; i++) {
		while(p < i && a[i] - a[p + 1] >= B) p++;
		if(last - 1 <= p) f[i] = (presum[p] - (last == 1 ? 0 : presum[last - 2]) + MOD) % MOD;
		presum[i] = (presum[i - 1] + f[i]) % MOD;
		if(a[i] - a[i - 1] < A) last = std::max(last, i);
		while(last >= 3 && last <= n && a[last] - a[last - 2] < A) last++;
		// printf("f[%d] = %lld\n", i, f[i]);
	}
	printf("%lld\n", f[n + 1]);
	return 0;
}