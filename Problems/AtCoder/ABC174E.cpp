#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

LL a[N];
int n, k;

bool check(LL x) {
	int cnt = 0;
	for(int i = 1; i <= n; i++) cnt += (a[i] + x - 1) / x - 1;
	if(cnt > k) return true;
	else return false;
}

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	LL l = 1, r = *std::max_element(a + 1, a + n + 1);
	while(l < r) {
		LL mid = l + ((r - l) >> 1);
		// printf("l = %lld, r = %lld, mid = %lld\n", l, r, mid);
		if(check(mid)) l = mid + 1;
		else r = mid;
	}
	// printf("l = %lld, r = %lld\n", l, r);
	printf("%lld\n", l);
	return 0;
}