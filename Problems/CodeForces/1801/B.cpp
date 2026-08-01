#include <cstdio>
#include <algorithm>
#include <deque>
#include <set>

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
struct Node { int a, b; } a[N];
bool operator<(Node x, Node y) { return x.a < y.a; }

int mx[N];
std::set<int> st;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		st.clear();
		scanf("%d", &n);
		for(int i = 1; i <= n + 1; i++) mx[i] = 0;
		for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].a, &a[i].b);
		std::sort(a + 1, a + n + 1);
		// for(int i = 1; i <= n; i++) printf("%d: %d %d\n", i, a[i].a, a[i].b);
		for(int i = n; i >= 1; i--) mx[i] = std::max(mx[i + 1], a[i].b);
		// for(int i = 1; i <= n; i++) printf("mx[%d] = %d\n", i, mx[i]);
		int ans = INF;
		st.insert(0);
		bool has_0 = false;
		for(int i = 1; i <= n; i++) {
			if(i == n && !has_0) st.erase(0);
			auto it = st.lower_bound(a[i].a);
			if(it != st.begin()) ans = std::min(ans, std::abs(a[i].a - std::max(mx[i + 1], *std::prev(it))));
			if(it != st.end()) ans = std::min(ans, std::abs(a[i].a - std::max(mx[i + 1], *it)));
			has_0 |= a[i].b == 0;
			st.insert(a[i].b);
			// printf("i = %d, ans = %d\n", i, ans);
		}
		printf("%d\n", ans);
	}
	return 0;
} /*
2
2
1 2
2 1
5
1 5
2 7
2 5
3 3
4 10

*/