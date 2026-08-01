#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = 2e5 + 5;

struct Node { int a, b, c, id, ans, cnt; } a[N];
int n, m;

namespace BIT {
	int c[N];
	inline void add(int qind, int qadd) { while(qind <= m) c[qind] += qadd, qind += (qind & -qind); }
	inline int query(int qind) { int ret = 0; while(qind) ret += c[qind], qind -= (qind & -qind); return ret; }
}

void solve(int l, int r) {
	if(l >= r) return;
	int mid = (l + r) / 2;
	solve(l, mid), solve(mid + 1, r);
	std::sort(a + l, a + mid + 1, [=](const Node &x, const Node &y) { return x.b == y.b ? x.c < y.c : x.b < y.b; });
	std::sort(a + mid + 1, a + r + 1, [=](const Node &x, const Node &y) { return x.b == y.b ? x.c < y.c : x.b < y.b; });
	// printf("========solve %2d .. %-2d========\n", l, r);
	// printf("    [l .. mid]: %d .. %d = [", l, mid);
	// for(int i = l; i <= mid; i++) printf("(%d, %d, %d) ", a[i].a, a[i].b, a[i].c);
	// printf("\b]\n");
	// printf("[mid + 1 .. r]: %d .. %d = [", mid + 1, r);
	// for(int i = mid + 1; i <= r; i++) printf("(%d, %d, %d) ", a[i].a, a[i].b, a[i].c);
	// printf("\b]\n");
	int i, j;
	for(i = l, j = mid + 1; j <= r; j++) {
		while(i <= mid && a[i].b <= a[j].b) BIT::add(a[i].c, a[i].cnt), i++;
		a[j].ans += BIT::query(a[j].c);
		// printf("case j=%d: [#%d .. #%d] <= #%d(%d), ans += %d\n", j, l, i - 1, j, a[j].b, BIT::query(1, a[j].c));
	}
	// printf("==============================\n");
	for(int k = l; k < i; k++) BIT::add(a[k].c, -a[k].cnt); // BIT::set(a[i].c, 0)
	// for(i = 0; i <= m; i++) assert(!BIT::query(i));
}

int out[N];

int main() {
	// freopen("D:\\Useless\\Temp\\P3810_2.in", "r", stdin);
	// freopen("D:\\Useless\\Temp\\P3810_2.myout", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].c), a[i].id = i, a[i].cnt = 1;
	std::sort(a + 1, a + n + 1,	[=](const Node &x, const Node &y) { return x.a != y.a ? x.a < y.a : (x.b != y.b ? x.b < y.b : x.c < y.c); });
	int cnt = 0;
	for(int i = 1; i <= n; i++)
		if(cnt && a[i].a == a[cnt].a && a[i].b == a[cnt].b && a[i].c == a[cnt].c) a[cnt].cnt++;
		else cnt++, a[cnt].a = a[i].a, a[cnt].b = a[i].b, a[cnt].c = a[i].c, a[cnt].cnt = 1;
	int n_ = n;
	n = cnt;
	solve(1, n);
	std::sort(a + 1, a + n + 1,	[=](const Node &x, const Node &y) { return x.a != y.a ? x.a < y.a : (x.b != y.b ? x.b < y.b : x.c < y.c); });
	// for(int i = n - 1; i >= 1; i--)
	// 	if(a[i].a == a[i + 1].a && a[i].b == a[i + 1].b && a[i].c == a[i + 1].c)
	// 		a[i].ans = a[i + 1].ans;
	// std::sort(a + 1, a + n + 1, [=](const Node &x, const Node &y) { return x.id < y.id; });
	// for(int i = 1; i <= n; i++) printf("a[%d] = %d\n", i, a[i].ans);
	for(int i = 1; i <= n; i++) a[i].ans += a[i].cnt - 1;
	for(int i = 1; i <= n; i++) out[a[i].ans] += a[i].cnt;
	for(int i = 0; i < n_; i++) printf("%d\n", out[i]);
	return 0;
}