#include <bits/stdc++.h>

const int N = 250 + 5;
const double eps = 1e-8;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;

int n;
struct Node { int x, y; } a[N];

double angle[N][N];
int ans = 1;
int f[N][N];
std::vector<std::pair<int, int>> order;
std::deque<int> q[N];
void solve(int base) {
	int m = base;
	while(m < n && a[m + 1].y == a[m].y) m++;
	// printf("solve(%d), m = %d\n", base, m);
	for(int i = 1; i <= n; i++) q[i].clear();
	for(int i = 1; i <= m; i++) for(int j = 1; j <= m; j++) f[i][j] = -INF;
	order.clear();
	for(int i = 1; i <= m; i++) for(int j = 1; j <= m; j++) if(i != j) order.push_back({i, j});
	std::sort(order.begin(), order.end(), [&](std::pair<int, int> x, std::pair<int, int> y) {
		#define f first
		#define s second
		if(std::abs(angle[x.f][x.s] - angle[y.f][y.s]) <= eps) {
			auto &ag = angle[x.f][x.s];
			if(ag <= -pi / 4 * 3 || ag >= pi / 4 * 3) return a[x.f].x > a[y.f].x;
			else if(-pi / 4 * 3 <= ag && ag <= -pi / 4) return a[x.f].y > a[y.f].y;
			else if(-pi / 4 <= ag && ag <= pi / 4) return a[x.f].x < a[y.f].x;
			else return a[x.f].y < a[y.f].y;
		} else return angle[x.f][x.s] < angle[y.f][y.s];
		#undef f
		#undef s
	});
	// for(auto [i, j] : order) printf("(%d, %d) angle = %.5f\n", i, j, angle[i][j]);
	for(auto [i, j] : order) {
		while(!q[i].empty() && angle[q[i].front()][i] <= angle[i][j] - pi + eps) q[i].pop_front();
		f[i][j] = (q[i].empty() ? -INF : f[q[i].front()][i]) + 1;
		if(i == base) f[i][j] = std::max(f[i][j], 1);
		// printf("q[%d].front() = %d\n", i, q[i].empty() ? -1 : q[i].front());
		while(!q[j].empty() && f[q[j].back()][j] < f[i][j]) q[j].pop_back();
		if(f[i][j] >= 0) {
			q[j].push_back(i);
			// printf("q[%d].push_back(%d)\n", j, i);
		}
	}
	for(int i = 1; i <= m; i++) if(i != base) ans = std::max(ans, f[i][base]);
}

int main() {
#ifndef DEBUG
	freopen("ada.in", "r", stdin);
	freopen("ada.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.y < y.y; });
	// for(int i = 1; i <= n; i++) printf("(%d, %d)\n", a[i].x, a[i].y);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) angle[i][j] = atan2(a[j].y - a[i].y, a[j].x - a[i].x);
	for(int i = 1; i <= n; i++) solve(i);
	printf("%d\n", ans);
	return 0;
}
