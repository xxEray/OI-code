#include <cstdio>
#include <algorithm>
#include <vector>
#include <bitset>

typedef long long LL;

const int N = 1e6 + 5;

std::bitset<N * 20> b;
LL cnt[100];
bool vis[N];

int main() {
	LL n, m;
	scanf("%lld%lld", &n, &m);
	for(int i = 2; i <= n; i++) {
		if(vis[i]) continue;
		LL power = 1;
		int c = 0;
		for(int j = 1; j <= 20; j++) {
			power *= i;
			if(power > n) break;
			vis[power] = true, c++;
		}
		// printf("%d: c = %d\n", i, c);
		cnt[c]++;
	}
	LL ans = 1;
	for(int i = 1; i <= 20; i++) {
		for(int j = 1; j <= m; j++) b[i * j] = true;
		ans += b.count() * cnt[i];
	}
	printf("%lld\n", ans);
	return 0;
}