#include <bits/stdc++.h>
#include "matrix.h"

#ifdef DEBUG
	#define msg(...) fprintf(stderr, __VA_ARGS__)
#else
	#define msg(...) ((void)0)
#endif

typedef long long LL;

namespace {
	int n;
	LL K;
	std::map<std::pair<int, int>, LL> mp;
	LL get(int x, int y) {
		// msg("asked (%d, %d)\n", x, y);
		if(mp.count({x, y})) return mp[{x, y}];
		else return mp[{x, y}] = query(x, y);
	}
	bool check(LL val) {
		// msg("check %lld\n", val);
		LL cnt = 0;
		int x = 1, y = n;
		while(x <= n && y >= 1) {
			// msg("x = %d, y = %d\n", x, y);
			if(get(x, y) > val) y--;
			else {
				cnt += y;
				x++;
			}
		}
		return cnt >= K;
	}
}

LL solve(int n_, LL K_) {
	n = n_, K = K_;
	LL l = 0, r = 1e18;
	while(l < r) {
		LL mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	return l;
} /*
3 5
0
1 2 5
3 4 6
7 8 9

*/