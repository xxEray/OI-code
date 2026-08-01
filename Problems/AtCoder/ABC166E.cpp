#include <cstdio>
#include <cstring>

const int N = 2e5 + 5;

int a[N];
int n;

long long cnt[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	long long ans = 0;
	for(int i = n; i >= 1; i--) {
		if(1 <= a[i] + i && a[i] + i <= n) ans += cnt[a[i] + i];
		if(1 <= i - a[i] && i - a[i] <= n) cnt[i - a[i]]++;
	}
	printf("%lld\n", ans);
	return 0;
} /*
if i > j
i - j = ai + aj
i - ai = aj + j
*/