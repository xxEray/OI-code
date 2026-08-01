#include <cstdio>
#include <algorithm>
#include <map>

typedef long long LL;

const int N = 3e5 + 5;

LL a[N];
int n;

LL sum[N];
std::map<LL, int> mp[2];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		mp[0].clear(), mp[1].clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		LL ans = 0;
		for(int i = 0; i <= n; i++) {
			sum[i] = a[i] - sum[i - 1];
			ans += mp[i & 1][sum[i]] + mp[!(i & 1)][-sum[i]];
			if(sum[i] < 0) sum[i] = 0, mp[0].clear(), mp[1].clear();
			mp[i & 1][sum[i]]++;
		printf("%lld\n", ans);
	}
	return 0;
} /*
1
11
1 1 1 1 0 1 0 1 2 1 2

  1 1 1 1 0 1 0  1 2 1  2
0 1 2 3 4 5 6 7  8 9 10 11
0 1 0 1 0 0 1 -1 1 1 0  2
[1, 2]
[2, 3]
[1, 4], [3, 4]
[5, 5], [3, 5], [1, 5]
[7, 7]
[8, 10]
*/