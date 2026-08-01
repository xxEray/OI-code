#include <bits/stdc++.h>

const int N = 5e5 + 5;

int n;
int a[N];

struct BIT {
	int t[N];
	void set(int x, int v) { while(x <= n) t[x] = std::max(t[x], v), x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret = std::max(ret, t[r]), r -= r & -r; return ret; }
} bit;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::vector<int> vct;
	int last = 0;
	for(int i = 1; i <= n; i++)
		if(a[i] > last) last = a[i];
		else vct.emplace_back(a[i]);
	int m = vct.size();
	int ans = 0;
	for(int v : vct) {
		int f = bit.query(v - 1) + 1;
		bit.set(v, f);
		ans = std::max(ans, f);
	}
	printf("%d\n", ans + (n - m));
	return 0;
}