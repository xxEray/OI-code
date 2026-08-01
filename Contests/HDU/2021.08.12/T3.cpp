#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long long LL;

const int N = 5000 + 5;

struct Point { LL x, y; } a[N];
int n;

LL distance(const Point &a, const Point &b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }

struct Distance { int x, y; LL d; } dis[N * N];
bool operator<(const Distance &a, const Distance &b) { return a.d < b.d; }
int cdis;

int fa[N];
int find(int x) {
	int y = x, t;
	while(fa[y] != y) y = fa[y];
	while(fa[x] != x) t = fa[x], fa[x] = y, x = t;
	return y;
}
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

bool check(int r) {
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 1; i <= r; i++) merge(dis[i].x, dis[i].y);
	for(int i = 2; i <= n; i++) if(find(i) != find(1)) return true;
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].x, &a[i].y);
		cdis = 0;
		for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) dis[++cdis] = {i, j, distance(a[i], a[j])};
		std::sort(dis + 1, dis + cdis + 1);
		int l = 1, r = cdis;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(check(mid)) l = mid + 1;
			else r = mid;
		}
		printf("%lld\n", dis[l].d);
	}
	return 0;
}