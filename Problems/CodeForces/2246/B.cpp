#include <bits/stdc++.h>
#include <cassert>

typedef long long LL;

int n;

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }
LL lcm(LL x, LL y) { return x / gcd(x, y) * y; }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		if(n == 1) { puts("1"); continue; }
		else if(n == 2) { puts("-1"); continue; }
		std::set<LL> st;
		st.emplace(2), st.emplace(3), st.emplace(6);
		while((int)st.size() < n) {
			for(LL x : st) {
				if(x % 2 == 0 && !st.count(x / 2 * 3) && !st.count(x * 3)) {
					st.erase(x), st.emplace(x / 2 * 3), st.emplace(x * 3);
					break;
				}
				if(x % 3 == 0 && !st.count(x / 3 * 4) && !st.count(x * 4)) {
					st.erase(x), st.emplace(x / 3 * 4), st.emplace(x * 4);
					break;
				}
			}
		}
		// for(LL x : st) printf("%lld ", x);
		LL lm = 1;
		for(LL x : st) lm = lcm(lm, x);
		for(auto it = st.rbegin(); it != st.rend(); ++it) printf("%lld ", lm / *it);
		puts("");
	}
	return 0;
}