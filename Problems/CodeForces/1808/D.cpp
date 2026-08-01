#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

int n;
int K;
LL a[N];
int lb[N], rb[N];

LL cnt[2][N];
LL tot[2];

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = (K + 1) / 2; i <= n; i++) lb[i] = std::max(i - K + 1, K + 1 - i), rb[i] = std::min(i, 2 * (n - (K + 1) / 2 + 1) - i);
	LL ans = 0;
	int l = 1, r = 0;
	for(int i = (K + 1) / 2; i <= n; i++) {
		while(r < rb[i]) r++, cnt[r & 1][a[r]]++, tot[r & 1]++;
		while(l > lb[i]) l--, cnt[l & 1][a[l]]++, tot[l & 1]++;
		while(r > rb[i]) cnt[r & 1][a[r]]--, tot[r & 1]--, r--;
		while(l < lb[i]) cnt[l & 1][a[l]]--, tot[l & 1]--, l++;
		ans += tot[i & 1] - cnt[i & 1][a[i]];
		// printf("i = %d, l = %d, r = %d, ans = %lld\n", i, lb[i], rb[i], ans);
	}
	printf("%lld\n", ans);
	return 0;
}