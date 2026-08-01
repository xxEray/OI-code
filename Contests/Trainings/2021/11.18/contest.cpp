#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 5e5 + 5;

LL a[N];
int n;

bool cmp(LL x, LL y) { return x > y; }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	std::sort(a + 1, a + n + 1);
//	for(int i = 1; i <= n; i++) printf("%lld%c", a[i], " \n"[i == n]);
	LL sum1 = 0, sum2 = 0, sum3 = 0, ans = -1;
	for(int i = 5; i <= n; i++) {
		sum3 = a[i - 4] +  a[i - 3] + a[i - 2] + a[i - 1];
		int l = i + 1, r = n;
		while(l < r) {
			int mid = (l + r) >> 1;
			sum2 = a[mid] + a[i];
			int q = std::lower_bound(a + 1, a + n + 1, sum2) - a - 1;
			sum1 = a[q];
			if(q > mid && sum3 > sum2 && sum2 > sum1) l = mid + 1;
			else r = mid;
		}
		int p = std::lower_bound(a + i + 1, a + n + 1, a[l - 1]) - a;
		sum2 = a[p] + a[i];
		int q = std::lower_bound(a + 1, a + n + 1, sum2) - a - 1;
		sum1 = a[q];
//		printf("i = %d, p = %d, q = %d, [%lld, %lld, %lld]\n", i, p, q, sum1, sum2, sum3);
		if(p <= i || q <= p || sum3 <= sum2 || sum2 <= sum1) continue;
		ans = std::max(ans, sum1 + sum2 + sum3);
	}
	printf("%lld\n", ans);
	return 0;
} /*
10
14 12 7 12 3 16 11 14 10 9 
*/
