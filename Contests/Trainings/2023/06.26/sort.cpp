#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n;
int a[N];

int lb[N], rb[N];

struct BIT {
	int t[N];
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
} bit;
std::vector<int> q[N];

int main() {
#ifndef DEBUG
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::vector<int> stk;
	for(int i = 1; i <= n; i++) {
		while(!stk.empty() && a[stk.back()] <= a[i]) stk.pop_back();
		lb[i] = (stk.empty() ? 0 : stk.back());
		stk.push_back(i);
	}
	stk.clear();
	for(int i = n; i >= 1; i--) {
		while(!stk.empty() && a[stk.back()] >= a[i]) stk.pop_back();
		rb[i] = (stk.empty() ? n + 1 : stk.back());
		stk.push_back(i);
	}
	for(int i = 1; i <= n; i++) if(lb[i]) q[lb[i]].push_back(i);
	long long ans = 0;
	for(int i = 1; i <= n; i++) {
		if(rb[i] <= n) bit.add(rb[i], 1);
		for(int j : q[i]) ans += bit.query(j);
	}
	printf("%lld\n", ans + 1);
	return 0;
}