#include <cstdio>
#include <algorithm>
#include <map>

typedef long long LL;

const int N = 2e5 + 5;

int a[N];
int n;

std::map<int, int> cnt;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		cnt.clear();
		scanf("%d", &n);
		LL sum = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), cnt[a[i]]++, sum += a[i];
		if(2 * sum % n) { puts("0"); continue; }
		LL k = 2 * sum / n;
		LL ans = 0;
		for(int i = 1; i <= n; i++) ans += cnt[k - a[i]], ans -= (a[i] * 2LL == k);
		printf("%lld\n", ans / 2);
	}
	return 0;
}