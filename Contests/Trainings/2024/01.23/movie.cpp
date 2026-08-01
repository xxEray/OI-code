#include <bits/stdc++.h>

typedef long long LL;

const int N = 2000 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, Q;

int l[N], r[N];

LL sum(LL x, LL y) { return (x + y) * (y - x + 1) / 2; }

struct SegmentTree {

} seg;
std::priority_queue<std::pair<LL, int>, std::vector<std::pair<LL, int>>, std::greater<>> q[N], q2;

int main() {
#ifndef DEBUG
	freopen("movie.in", "r", stdin);
	freopen("movie.out", "w", stdout);
#endif
	scanf("%d%d", &Q, &n);
	for(int i = 1; i <= n; i++) l[i] = -1;
	for(int i = 1; i <= n; i++) q2.emplace();
	while(Q--) {
		int x;
		scanf("%d", &x);
		int p = 0, cl = 0, cr = 0, al = 0, ar = 0;
		LL val = LLINF;
		for(int i = 1; i <= n; i++) {
			if(l[i] == -1) {
				LL nval = (LL)x * std::abs((n + 1) / 2 - i) + ((x & 1) ? (LL)((x - 1) / 2) * ((x - 1) / 2 + 1) : (LL)(x / 2) * (x / 2 + 1) / 2 + (LL)(x / 2 - 1) * (x / 2) / 2);
				if(nval < val) p = i, val = nval, cl = (n + 1) / 2 - x / 2 - 1, cr = (n + 1) / 2 + (x - 1) / 2 + 1, al = cl + 1, ar = cr - 1;
			} else {
				if(l[i] >= x) {
					LL nval = (LL)x * std::abs((n + 1) / 2 - i) + sum((n + 1) / 2 - l[i], (n + 1) / 2 - (l[i] - x + 1));
					if(nval < val) p = i, val = nval, cl = l[i] - x, cr = r[i], al = l[i] - x + 1, ar = l[i];
				}
				if(n - r[i] + 1 >= x) {
					LL nval = (LL)x * std::abs((n + 1) / 2 - i) + sum(r[i] - (n + 1) / 2, (r[i] + x - 1) - (n + 1) / 2);
					if(nval < val) p = i, val = nval, cl = l[i], cr = r[i] + x, al = r[i], ar = r[i] + x - 1;
				}
			}
		}
		if(val >= LLINF / 2) puts("-1");
		else {
			l[p] = cl, r[p] = cr;
			printf("%d %d %d\n", p, al, ar);
		}
	}
	return 0;
}