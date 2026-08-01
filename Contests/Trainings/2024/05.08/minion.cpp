#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

int n, m;
struct Node { LL l, r; } a[N];

void preprocess() {
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.l == y.l ? x.r > y.r : x.l < y.l; });
	int j = 0;
	LL r = 0;
	for(int i = 1; i <= n; i++) if(a[i].l <= a[i].r && a[i].r > r) {
		a[++j] = a[i];
		r = a[i].r;
	}
	n = j;
	// for(int i = 1; i <= n; i++) printf("[%lld, %lld]\n", a[i].l, a[i].r);
}

struct DP {
	LL cost; int cnt;
	DP() {}
	DP(LL cost_, int cnt_) : cost(cost_), cnt(cnt_) {}
};
bool operator<(const DP &x, const DP &y) { return x.cost == y.cost ? x.cnt > y.cnt : x.cost < y.cost; }
DP operator+(const DP &x, const DP &y) { return DP(x.cost + y.cost, x.cnt + y.cnt); }
DP f[N];
DP calc(LL penalty) {
	DP pre = {0, 0};
	for(int i = 0; i <= n; i++) f[i] = DP(0, 0);
	for(int i = 1, j = 1, k = 1; i <= n; i++) {
		while(j < i && a[j].r < a[i].l) pre = std::max(pre, f[j]), j++;
		while(k < i && (i == n || a[k].r < a[i + 1].l)) k++;
		f[i] = std::max(f[i], pre + DP(a[i].r - a[i].l + 1 - penalty, 1));
		for(int p = j; p < k; p++)
			f[i] = std::max(f[i], f[p] + DP(a[i].r - a[p].r - penalty, 1));
	}
	DP ans = {0, 0};
	for(int i = 1; i <= n; i++) ans = std::max(ans, f[i]);
	// printf("calc(%lld)\n", penalty);
	// for(int i = 1; i <= n; i++) printf("  f[%d] = {%lld, %d}\n", i, f[i].cost, f[i].cnt);
	return ans;
}

int main() {
#ifndef DEBUG
	freopen("minion.in", "r", stdin);
	freopen("minion.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].l, &a[i].r), a[i].r--;
	preprocess();
	m = std::min(m, n);
	LL l = 0, r = 1e18;
	while(l < r) {
		LL mid = (l + r) >> 1;
		if(calc(mid).cnt > m) l = mid + 1;
		else r = mid;
	}
	auto ans = calc(l);
	printf("%lld\n", ans.cost + l * ans.cnt);
	return 0;
} /*
5 2
1 7
4 6
4 9
6 12
10 19
*/