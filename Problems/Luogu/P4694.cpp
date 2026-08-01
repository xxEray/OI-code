#include <cstdio>
#include <algorithm>
#include <set>

typedef long long LL;

const int N = 5e5 + 5;

int n, m;
LL a[N], b[N];

std::multiset<LL> st;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	LL ans = 0;
	for(int i = 1; i <= n; i++) {
		st.insert(a[i]);
		auto it = st.begin();
		ans += *it + b[i];
		st.erase(it), st.insert(b[i]);
	}
	printf("%lld\n", ans);
	return 0;
}