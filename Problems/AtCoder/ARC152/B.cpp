#include <cstdio>
#include <algorithm>
#include <set>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
LL L;
LL a[N];

LL calc(LL x, LL y) { return 2 * L + std::abs(x + y - (L - x + L - y)); }
std::set<LL> st;

int main() {
	scanf("%d%lld", &n, &L);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	LL ans = LLINF;
	for(int i = 1; i <= n; i++) st.insert(a[i]);
	for(int i = 1; i <= n; i++) {
		auto it = st.lower_bound(L - a[i] + 1);
		if(it != st.end()) ans = std::min(ans, calc(a[i], *it));
		if(it != st.begin()) ans = std::min(ans, calc(a[i], *std::prev(it)));
	}
	printf("%lld\n", ans);
	return 0;
} /*
*/