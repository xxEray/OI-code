#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int a[N], b[N];
int n, m;

int rmost[N];

struct BIT {
	int t[N];
	int query(int r) { int ret = 0; while(r) ret = ret + t[r], r -= (r & -r); return ret; }
	void modify(int x, int y) { while(x <= m + 1) t[x] = t[x] + y, x += (x & -x); }
	void modify(int l, int r, int v) { modify(r + 1, -v), modify(l, v); }
} bit;

int main() {
	scanf("%d%d", &n, &m);
	int lmost = m;
	for(int i = 1; i <= m; i++) rmost[i] = i;
	for(int i = 1; i <= n; i++) {
		scanf("%d%d", &a[i], &b[i]);
		rmost[a[i] + 1] = std::max(rmost[a[i] + 1], b[i]);
		rmost[1] = std::max(rmost[1], a[i]);
		lmost = std::min(lmost, b[i]);
	}
	// for(int l = 1; l <= lmost; l++) printf("l = %d, rmost = %d\n", l, rmost[l]);
	int r = rmost[1];
	for(int l = 1; l <= lmost; l++) {
		if(r < rmost[l]) r = rmost[l];
		// printf("[%d, %d] += 1\n", r - l + 1, m - l + 1);
		bit.modify(r - l + 1, m - l + 1, 1);
	}
	for(int i = 1; i <= m; i++) printf("%d ", bit.query(i));
	return 0;
}