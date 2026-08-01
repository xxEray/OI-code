#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n;
LL a[N];

int m;
int half[N];
LL val[N];
void discrete() {
	m = 0;
	for(int i = 1; i <= n; i++) val[++m] = a[i];
	std::sort(val + 1, val + m + 1);
	m = std::unique(val + 1, val + m + 1) - val - 1;
	for(int i = 1; i <= n; i++) a[i] = std::lower_bound(val + 1, val + m + 1, a[i]) - val;
	for(int i = 1, j = 0; i <= m; i++) {
		while(val[j + 1] )
	}
}

struct BIT {
	int t[N];
	void modify(int x, int v) { while(x <= m) t[x] = std::max(t[x], v), x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret = std::max(ret, t[r]), r -= r & -r; return ret; }
} bit;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		discrete();
	}
	return 0;
}