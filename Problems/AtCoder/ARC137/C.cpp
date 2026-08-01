#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 3e5 + 5;

bool a[N][35];
int n;

LL cnt[35];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int x; scanf("%d", &x);
		for(int j = 0; j <= 30; j++) a[i][j] = (x >> j & 1);
	}
	for(int i = 1; i <= n; i++) for(int j = 0; j <= 30; j++) cnt[j] += a[i][j];
	LL ans = 0;
	for(int j = 0; j <= 30; j++) ans += cnt[j] << j;
	for(int i = 1; i <= n; i++) {
		LL ret = 0;
		for(int j = 0; j <= 30; j++)
			if(a[i][j]) ret += (n - cnt[j]) << j;
			else ret += cnt[j] << j;
		ans = std::max(ans, ret);
	}
	printf("%lld\n", ans);
	return 0;
}