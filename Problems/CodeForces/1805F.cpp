#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 1e9 + 7;

int n;
LL a[N], b[N];

LL sum = 0;

bool check(LL x, int m) {
	int cnt = 0;
	for(int i = 1; i <= m; i++)
		for(int j = i + 1; j <= m; j++)
			if(a[i] + a[j] <= x) {
				cnt++;
				if(cnt >= m) return false;
			} else break;
	return true;
}

void solve(int m) {
	LL l = a[1] + a[2], r = a[m - 1] + a[m];
	while(l < r) {
		LL mid = (l + r) >> 1;
		if(check(mid, m)) l = mid + 1;
		else r = mid;
	}
	// printf("pivot = %lld, ", l);
	int c = 0;
	for(int i = 1; i <= m; i++)
		for(int j = i + 1; j <= m; j++)
			if(a[i] + a[j] <= l) b[++c] = a[i] + a[j];
			else break;
	for(int i = c + 1; i <= m; i++) b[i] = l;
	std::sort(b + 1, b + m + 1);
	for(int i = 1; i <= m; i++) a[i] = b[i];
	sum = (sum * 2 + a[1]) % MOD;
	for(int i = 2; i <= m; i++) a[i] -= a[1];
	a[1] = 0;
	// for(int i = 1; i <= m; i++) printf("%lld ", a[i]);
	// puts("");
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	std::sort(a + 1, a + n + 1);
	// for(int i = 1; i <= n; i++) printf("%lld ", a[i]);
	// puts("");
	for(int i = n; i >= 2; i--) solve(std::min(64, i));
	printf("%lld\n", (sum + a[1]) % MOD);
	return 0;
}