#include <cstdio>
#include <algorithm>
#include <set>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int Q;
std::set<LL> st;

int main() {
	scanf("%d", &Q);
	LL x, y;
	scanf("%lld%lld", &x, &y);
	st.insert(x + y), st.insert(x - y);
	while(Q--) {
		int t;
		scanf("%d%lld%lld", &t, &x, &y);
		if(t == 1) st.insert(x + y), st.insert(x - y);
		else {
			LL ans = LLINF;
			auto it = st.lower_bound(x);
			if(it != st.end()) ans = std::min(ans, *it <= y ? 0 : *it - y);
			it = st.upper_bound(x);
			if(it != st.begin()) it--, ans = std::min(ans, *it >= x ? 0 : x - *it);
			printf("%lld\n", ans);
		}
	}
	return 0;
}