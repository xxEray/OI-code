#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 99999 + 5;
const int INF = 0x3f3f3f3f;

int n, m;

struct Node {
	int l, r, l0, r0;
	bool operator<(const Node &rhs) const { return r == rhs.r ? l < rhs.l : r < rhs.r; }
} a[N];
bool cmp_lu(int x, int y) { return a[x].l < a[y].l; }

std::vector<int> ans;

int main() {
	scanf("%d", &m);
	for(n = 1;;) {
		int l, r;
		if(scanf("%d%d", &l, &r) != 2) break;
		if(!l && !r) break;
		if(r <= 0 || l >= m || l == r) continue;
		a[n].l = std::max(l, 0), a[n].r = std::min(r, m);
		a[n].l0 = l, a[n].r0 = r;
		n++;
	}
	if(n == 1) { puts("No solution"); return 0; }
	a[n].l = INF, a[n].r = INF;
	std::sort(a + 1, a + n + 1);
	int cnt = 0, least = 0;
	for(int i = 1; i < n; i++) {
		if(least >= m) break;
		if(a[i].l > least) { puts("No solution"); return 0; }
		else if(a[i + 1].l > least && a[i].r > least) least = a[i].r, cnt++, ans.push_back(i);
	}
	if(least < m) { puts("No solution"); return 0; }
	std::sort(ans.begin(), ans.end(), cmp_lu);
	printf("%d\n", cnt);
	for(auto x : ans) printf("%d %d\n", a[x].l0, a[x].r0);
	return 0;
} /*
1
-1 0
-1 1
0 0
*/