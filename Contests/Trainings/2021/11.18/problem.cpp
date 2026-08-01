#include <cstdio>
#include <algorithm>
#include <set>

typedef long long LL;

const int N = 1000 + 5;

LL a[N], b[N], t[N];
int n, m, Type;

std::multiset<LL> st;

int main() {
#ifndef DEBUG
	freopen("problem.in", "r", stdin);
	freopen("problem.out", "w", stdout); 
#endif
	scanf("%d%d%d", &n, &m, &Type);
	for(int i = 1; i <= m; i++) scanf("%1lld", &t[i]);
	for(int i = 1; i <= m; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	long long ans = 0;
	for(int i = 1; i <= n; i++) {
		st.clear();
		b[i] = (b[i] + Type * ans) % 1000000000;
		for(int j = 1; j <= i; j++) st.insert(b[j]);
		for(int j = 1; j <= m; j++) st.insert(a[j]), st.erase(t[j] ? --st.end() : st.begin());`
		ans = 0;
		for(LL x : st) ans += x;
		printf("%lld ", ans);
	}
	return 0;
} /*
3 2 0
01
4 2
3 5 1
*/
