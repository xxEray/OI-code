#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n, Q;
struct Node { int x, y, w; } a[N];

int tl[N], tr[N], tu[N], td[N];

void chkmax(int &x, int y) { /* printf("chkmax %d\n", y); */ if(x < y) x = y; }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &Q);
		for(int i = 1; i <= n; i++) {
			int x, y;
			scanf("%d%d%d", &x, &y, &a[i].w);
			a[i].x = x + y, a[i].y = x - y;
		}
		std::sort(a + 1, a + n + 1, [](Node x, Node y) { return x.w > y.w; });
		// for(int i = 1; i <= n; i++) printf("(%d, %d), w = %d\n", a[i].x, a[i].y, a[i].w);
		// u: min(w_i, x - x_i)
		tl[0] = INF, tr[0] = -INF, tu[0] = INF, td[0] = -INF;
		for(int i = 1; i <= n; i++) {
			tl[i] = std::min(tl[i - 1], a[i].y);
			tr[i] = std::max(tr[i - 1], a[i].y);
			tu[i] = std::min(tu[i - 1], a[i].x);
			td[i] = std::max(td[i - 1], a[i].x);
			// printf("pre[%d]: u=%d d=%d l=%d r=%d\n", i, tu[i], td[i], tl[i], tr[i]);
		}
		a[n + 1].w = 0;
		while(Q--) {
			int x0, y0, x, y;
			scanf("%d%d", &x0, &y0);
			x = x0 + y0, y = x0 - y0;
			// printf("(%d, %d)\n", x, y);
			int ans = 0;
			int l, r;
			// u
			l = 1, r = n + 1;
			while(l < r) {
				int mid = (l + r) >> 1;
				if(x - tu[mid] > a[mid].w) r = mid;
				else l = mid + 1;
			}
			chkmax(ans, std::max(std::min(a[l].w, x - tu[l]), std::min(a[l - 1].w, x - tu[l - 1])));
			// d
			l = 1, r = n + 1;
			while(l < r) {
				int mid = (l + r) >> 1;
				if(td[mid] - x > a[mid].w) r = mid;
				else l = mid + 1;
			}
			chkmax(ans, std::max(std::min(a[l].w, td[l] - x), std::min(a[l - 1].w, td[l - 1] - x)));
			// l
			l = 1, r = n + 1;
			while(l < r) {
				int mid = (l + r) >> 1;
				if(y - tl[mid] > a[mid].w) r = mid;
				else l = mid + 1;
			}
			chkmax(ans, std::max(std::min(a[l].w, y - tl[l]), std::min(a[l - 1].w, y - tl[l - 1])));
			// r
			l = 1, r = n + 1;
			while(l < r) {
				int mid = (l + r) >> 1;
				if(tr[mid] - y > a[mid].w) r = mid;
				else l = mid + 1;
			}
			chkmax(ans, std::max(std::min(a[l].w, tr[l] - y), std::min(a[l - 1].w, tr[l - 1] - y)));
			printf("%d\n", ans);
		}
	}
	return 0;
} /*
1
3 4
2 3 9
5 1 6
1 5 7
1 5
2 2
4 3
10 10
*/