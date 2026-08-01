#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 3e5 + 5;

int n;
int a[N];

int cnt[N], sum[N];
LL f[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), cnt[a[i]] = 1;
	for(int i = 2; i <= 300000; i++) f[i] = 1;
	for(int i = 2; i <= 300000; i++)
		for(int j = i + i; j <= 300000; j += i)
			f[j] -= f[i];
	for(int i = 1; i <= 300000; i++) sum[i] = sum[i - 1] + cnt[i];
	LL ans = 0;
	for(int i = 2; i <= 300000; i++) {
		int tot = 0, all = 0;
		for(int j = i; j <= 300000; j += i) all += cnt[j];
		for(int j = i; j <= 300000; j += i) if(cnt[j]) {
			LL ret = 0;
			ret += (LL)sum[j - 1] * tot;
			tot++;
			ret -= (LL)sum[j] * (all - tot);
			// printf("%d, %d: ans += %lld * %lld\n", i, j, f[i], ret);
			ans += f[i] * ret;
		}
	}
	printf("%lld\n", (LL)n * (n - 1) * (n - 2) / 6 - ans);
	return 0;
}