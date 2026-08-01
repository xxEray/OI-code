#include <cstdio>
#include <algorithm>
#include <set>

const int N = 2e5 + 5;

int n, m, X;
struct Node { int l, r; } a[N];

std::set<int> st;

int main() {
	scanf("%d%d%d", &n, &m, &X);
	for(int i = 1; i <= m; i++) scanf("%d%d", &a[i].l, &a[i].r);
	std::sort(a + 1, a + m + 1, [&](Node x, Node y) { return x.r > y.r; });
	int mnl = X;
	for(int i = 1; i <= m; i++) if(a[i].r >= mnl) mnl = std::min(mnl, a[i].l);
	for(int i = 1; i <= m; i++) if(a[i].r >= mnl && a[i].l <= X) st.insert(a[i].l);
	int mxr = X;
	std::sort(a + 1, a + m + 1, [&](Node x, Node y) { return x.l < y.l; });
	for(int i = 1; i <= m; i++) if(a[i].l <= mxr) mxr = std::max(mxr, a[i].r);
	for(int i = 1; i <= m; i++) if(a[i].l <= mxr && a[i].r >= X) st.insert(a[i].r);
	for(int x : st) if(x != X) printf("%d ", x);
	puts("");
	return 0;
}