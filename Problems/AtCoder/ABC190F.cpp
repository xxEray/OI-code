#include <cstdio>
#include <algorithm>

const int N = 3e5 + 5;
typedef long long LL;

int a[N];
int n;

namespace BIT {
	int t[N];
	void add(int x, int y) { while(x <= n) t[x] += y, x += (x & -x); }
	int query(int x) { int ret = 0; while(x > 0) ret += t[x], x -= (x & -x); return ret; }
	int query(int l, int r) { return query(r) - query(l - 1); }
}

int main() {
	std::scanf("%d", &n);
	for(int i = 1; i <= n; i++) std::scanf("%d", &a[i]), a[i]++;
	LL ans = 0;
	for(int i = 1; i <= n; i++) {
		ans += BIT::query(a[i], n); // [a_i + 1 .. n]
		BIT::add(a[i], 1);
	}
	for(int i = 1; i <= n; i++) {
		std::printf("%lld\n", ans);
		ans -= a[i] - 1;
		ans += n - a[i];
	}
	return 0;
}