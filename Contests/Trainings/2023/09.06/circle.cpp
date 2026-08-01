#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n;
int a[N], q[N];
LL p[N];

int order[N];

struct BIT {
	LL t[N];
	void init() { for(int i = 1; i <= n; i++) t[i] = 0; }
	void add(int x, LL v) { assert(1 <= x && x <= n); while(x <= n) t[x] += v, x += x & -x; }
	LL query(int r) { assert(0 <= r && r <= n); LL ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
} bit;

int tmp[N];
void discrete() {
	int c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = a[i];
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i] = std::lower_bound(tmp + 1, tmp + c + 1, a[i]) - tmp;
	c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = q[i];
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) q[i] = std::lower_bound(tmp + 1, tmp + c + 1, q[i]) - tmp;
}

int main() {
#ifndef DEBUG
	freopen("circle.in", "r", stdin);
	freopen("circle.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) a[i] += a[i - 1];
		if(a[n] < 0) { puts("-1"); continue; }
		else if(a[n] == 0) {
			bool all_0 = true;
			for(int i = 1; i <= n; i++) all_0 &= (a[i] == 0);
			puts(all_0 ? "0" : "-1");
			continue;
		}
		for(int i = 1; i <= n; i++) {
			p[i] = a[i] / a[n], q[i] = a[i] % a[n];
			if(q[i] < 0) q[i] += a[n], p[i]--;
		}
		discrete();
		LL ans = 0;
		// for(int i = 1; i <= n; i++) printf("%d: a = %d, p = %lld, q = %d\n", i, a[i], p[i], q[i]);
		bit.init();
		for(int i = 1; i <= n; i++) bit.add(a[i], 1);
		for(int i = 1; i <= n; i++) ans += bit.query(a[i] - 1) * p[i], ans -= (bit.query(n) - bit.query(a[i])) * p[i];
		bit.init();
		for(int i = 1; i <= n; i++) ans -= bit.query(a[i] - 1), bit.add(a[i], 1);
		bit.init();
		for(int i = 1; i <= n; i++) order[i] = i;
		std::sort(order + 1, order + n + 1, [&](int x, int y) { return a[x] < a[y]; });
		for(int i = 1; i <= n;) {
			int j = i;
			while(a[order[i]] == a[order[j]]) ans += bit.query(q[order[j]] - 1), j++;
			j = i;
			while(a[order[i]] == a[order[j]]) bit.add(q[order[j]], 1), j++;
			i = j;
		}
		printf("%lld\n", ans);
	}
	return 0;
} /*
3
3
2 2 ‐3
3
2 2 ‐5
3
0 0 0
*/