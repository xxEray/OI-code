#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n; LL kap, kaq, kbp, kbq;
struct Node { LL x, y; int f; } a[N];

LL tmp[N];
void discrete() {
	int c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = a[i].x;
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i].x = std::lower_bound(tmp + 1, tmp + c + 1, a[i].x) - tmp;
	c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = a[i].y;
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i].y = std::lower_bound(tmp + 1, tmp + c + 1, a[i].y) - tmp;
}

struct BIT {
	int t[N];
	void modify(int x, int v) { while(x <= n) t[x] = std::max(t[x], v), x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret = std::max(ret, t[r]), r -= r & -r; return ret; }
} bit;

int main() {
	scanf("%d%lld/%lld%lld/%lld", &n, &kap, &kaq, &kbp, &kbq);
	for(int i = 1; i <= n; i++) {
		LL x, y;
		scanf("%lld%lld", &x, &y);
		a[i].x = kbp * x - kbq * y, a[i].y = kaq * y - kap * x;
		if(a[i].x <= 0 || a[i].y <= 0) a[i].f = -1;
		// printf("(%lld, %lld)\n", a[i].x, a[i].y);
	}
	discrete();
	// puts(""); for(int i = 1; i <= n; i++) printf("(%lld, %lld) %d\n", a[i].x, a[i].y, a[i].f);
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.x < y.x; });
	for(int i = 1; i <= n; ) {
		int j;
		for(j = i; j <= n && a[j].x == a[i].x; j++) if(a[j].f != -1) a[j].f = bit.query(a[j].y - 1) + 1;
		for(j = i; j <= n && a[j].x == a[i].x; j++) if(a[j].f != -1) bit.modify(a[j].y, a[j].f);
		i = j;
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) ans = std::max(ans, a[i].f);
	printf("%d\n", ans);
	return 0;
} /*
15
2/1 2/0
3 1
6 2
9 3
12 4
15 5
2 1
4 2
5 3
7 4
1 3
3 4
2 5
4 5
1 6
6 6
*/