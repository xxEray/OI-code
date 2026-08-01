#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int a[N];
int n, m;

struct BIT {
	int t[N];
	void add(int x, int y) { while(x <= n) t[x] += y, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	void add(int l, int r, int v) { add(l, v), add(r + 1, -v);}
} bit;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) bit.t[i] = 0;
		int ans = 0;
		for(int _ = 1; _ <= m; _++) {
			int type, x, y;
			scanf("%d", &type);
			if(type == 1) {
				scanf("%d%d", &x, &y);
				bit.add(y + 1, n, y - x + 1);
			} else {
				scanf("%d", &x);
				ans ^= a[x - bit.query(x)];
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}