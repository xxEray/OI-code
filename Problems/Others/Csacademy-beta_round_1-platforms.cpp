#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

struct Segment { int l, r; } a[N];
int b[N];
int n, m;

namespace ST {
	const int D = 20;
	int f[N][D], log[N];
	void init() {
		b[0] = -INF, b[m + 1] = f[1][0] = f[m + 1][0] = INF, log[0] = -1;
		for(int i = 2; i <= m; i++) f[i][0] = b[i] - b[i - 1];
		for(int i = 1; i <= m + 1; i++) log[i] = log[i >> 1] + 1;
		for(int j = 1; j < 20; j++)
			for(int i = 1; i + (1 << j) - 1 <= m + 1; i++)
				f[i][j] = std::max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
	}
	int max(int l, int r) {
		if(l > r) return 0;
		int k = log[r - l + 1];
		return std::max(f[l][k], f[r - (1 << k) + 1][k]);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%d%d", &a[i].l, &a[i].r);
		if(a[i].l > a[i].r) std::swap(a[i].l, a[i].r);
	}
	for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
	std::sort(b + 1, b + m + 1);
	ST::init();
	LL ans = 0;
	for(int i = 1; i <= n; i++) {
		int ret1, ret2;
		int rlst = std::lower_bound(b, b + m + 2, a[i].l) - b, llst = std::upper_bound(b, b + m + 2, a[i].r) - b - 1;
		if(*std::upper_bound(b, b + m + 2, a[i].l) >= a[i].r) { /* printf("%d .. %d: continue\n", a[i].l, a[i].r); */ continue; }
		int l = rlst + 1, r = m + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(b[mid - 1] < a[i].l || ST::max(l, mid) < a[i].r - a[i].l) l = mid + 1;
			else r = mid;
		}
		ret1 = l;
		l = 2, r = llst;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(b[mid] > a[i].r || ST::max(mid, r) < a[i].r - a[i].l) r = mid;
			else l = mid + 1;
		}
		ret2 = l - 1;
		// printf("%d .. %d: %d>, %d<, %d->%d | %d->%d\n", a[i].l, a[i].r, rlst, llst, a[i].l, b[ret1 - 1], a[i].r, b[ret2]);
		ans += std::min(b[ret1 - 1] - a[i].l, a[i].r - b[ret2]);
	}
	printf("%lld\n", ans);
	return 0;
} /*
15 4
0 75
0 2804
0 3992
0 7700
0 8689
2560 2780
2560 4828
2560 5560
2560 7502
2560 7974
2581 4339
2581 4857
2581 5826
2581 7710
2581 9302
0 2560 2581 2587 
*/