#include <cstdio>
#include <algorithm>
#include <set>
#include <cassert>
using std::prev;
using std::next;

typedef long long LL;

const int N = 1e5 + 5;

int a[N];
int n;

std::set<int> st;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); a[x] = i; }
	st.insert(0), st.insert(n + 1);
	st.insert(a[n]);
	// for(int i = 1; i <= n; i++) { printf("%d ", a[i]); } puts("");
	LL ans = 0;
	for(int i = n - 1; i >= 1; i--) {
		auto rit = st.upper_bound(a[i]);
		auto lit = prev(rit);
		if(rit != prev(st.end())) ans += (LL)(*next(rit) - *rit) * (a[i] - *lit) * i;
		if(lit != st.begin()) ans += (LL)(*lit - *prev(lit)) * (*rit - a[i]) * i;
		// printf("%d: ans = %lld now\n", i, ans);
		st.insert(a[i]);
	}
	printf("%lld\n", ans);
	return 0;
}