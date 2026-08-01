#include <cstdio>
#include <algorithm>
#include <map>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

std::map<LL, int> a;
int n;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		a.clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) { LL x; scanf("%lld", &x); a[x]++; }
		LL ans = 0, cnt = 0, id = 0, lastans = LLINF;
		for(auto &p : a) {
			ans += (p.second + p.first - 1) / p.first * p.first;
			if(p.second % p.first) cnt++, id = p.first;
		}
		// printf("%d\n", ans);
		if(cnt == 0) printf("%lld\n", ans + 1);
		else {
			for(auto &p : a) {
				lastans = std::min(lastans, ans - p.first * (p.second % p.first == 1 || p.first == 1) + (cnt == 1 && id == p.first ? (p.first == 1 ? 2 : 1) : 0));
			}
			printf("%lld\n", lastans);
		}
	}
	return 0;
} /*
1
13
1 1 1 1 1 1 1 1 1 1 1 1 1
*/