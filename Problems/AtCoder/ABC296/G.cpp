#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cassert>

const int N = 2e5 + 5;
const double eps = 1e-8;

int n, m;
struct Point { int x, y; } a[N];
struct Query { int x, y, id; } q[N];

int out[N]; // -1 --- IN, 0 --- ON, 1 --- OUT

bool check(int )

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	for(int i = 1; i <= m; i++) scanf("%d%d", &q[i].x, &q[i].y), q[i].id = i;
	int basex = a[1].x, basey = a[1].y;
	for(int i = 1; i <= n; i++) a[i].x -= basex, a[i].y -= basey;
	for(int i = 1; i <= m; i++) q[i].x -= basex, q[i].y -= basey;
	std::sort(a + 2, a + n + 1, [&](Point x, Point y) { return atan2(x.y, x.x) < atan2(y.y, y.x); });
	std::sort(q + 1, q + m + 1, [&](Query x, Query y) { return atan2(x.y, x.x) < atan2(y.y, y.x); });
	int j = 2, last = n;
	for(int i = 1; i <= m; i++) {
		if(q[i].x == 0 && q[i].y == 0) { out[q[i].id]] = 0; continue; }
		while(j <= n && atan2(q[i].y, q[i].x) > atan2(a[j].y, a[j].x) + eps) last = j, j++;
		assert(atan2(a[last].y, a[last].x) + eps <= atan2(q[i].y, q[i].x) && atan2(q[i].y, q[i].x) <= atan2(a[i].y, a[i].x) + eps);
		if((a[j].y - q[i].y) * (q[i].x - a[last].x) == (q[i].y - a[last].y) * (a[j].x - q[i].x)) out[q[i].id] = 0;
		else if()
	}
	for(int i = 1; i <= m; i++) puts(out[i] == -1 ? "IN" : (out[i] == 0 ? "ON" : "OUT"));
	return 0;
}