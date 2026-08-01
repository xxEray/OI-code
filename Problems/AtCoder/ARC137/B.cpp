#include <cstdio>
#include <algorithm>
#include <set>

const int N = 3e5 + 5;
const int INF = 0x3f3f3f3f;

int a[N];
int n;

int sum[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum[i] = sum[i - 1] + (a[i] ? -1 : 1);
	int mn = 0, mx = 0;
	std::set<int> st;
	st.insert(sum[0]);
	for(int i = 1; i <= n; i++) {
		mn = std::min(mn, sum[i] - *st.rbegin());
		mx = std::max(mx, sum[i] - *st.begin());
		st.insert(sum[i]);
	}
	printf("%d\n", mx - mn + 1);
	return 0;
} /*
*/