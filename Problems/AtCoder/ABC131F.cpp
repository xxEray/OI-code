#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 1e5 + 5;

struct Point { int x, y; } a[N];
int n;

std::vector<int> vx[N], vy[N], elem[N];
int cntx[N], cnty[N];

int fa[N];
void init() { for(int i = 1; i <= n; i++) fa[i] = i; }
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y), vx[a[i].x].push_back(i), vy[a[i].y].push_back(i);
	init();
	for(int i = 1; i <= n; i++) {
		for(int j : vx[a[i].x]) merge(i, j);
		for(int j : vy[a[i].y]) merge(i, j);
	}
	for(int i = 1; i <= n; i++) elem[find(i)].push_back(i);
	LL ans = 0;
	for(int i = 1; i <= n; i++) if(!elem[i].empty()) {
		// for(int j : elem[i]) printf("%d ", j);
		// puts("");
		for(int j = 1; j <= 100000; j++) cntx[j] = cnty[j] = 0;
		for(int j : elem[i]) cntx[a[j].x]++, cnty[a[j].y]++;
		LL totx = 0, toty = 0;
		for(int j = 1; j <= 100000; j++) totx += (cntx[j] > 0), toty += (cnty[j] > 0);
		// printf("totx = %lld, toty = %lld\n", totx, toty);
		ans += totx * toty - elem[i].size();
	}
	printf("%lld\n", ans);
	return 0;
}