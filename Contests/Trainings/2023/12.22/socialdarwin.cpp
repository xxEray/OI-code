#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;
const double eps = 1e-20;

int n, m;
struct Point { int x, y; };
struct Query { int x, y, r, id; } q[N];

struct Convex {
	std::vector<Point> conv;
	bool type; // true - up, false - down
	void construct(std::vector<Point> points, bool type_) {
		conv.clear(), type = type_;
		std::sort(points.begin(), points.end(), [&](const Point &x, const Point &y) {
			if(x.x != y.x) return x.x < y.x;
			else return type ? (x.y > y.y) : (x.y < y.y);
		});
		auto compare = [&](const Point &x, const Point &y, const Point &z) -> bool { return ((LL)(y.y - x.y) * (z.x - y.x) < (LL)(z.y - y.y) * (y.x - x.x)) ^ type; };
		int lastx = -1e9;
		for(const auto &p : points) {
			if(p.x == lastx) continue;
			lastx = p.x;
			while(conv.size() >= 2 && !compare(conv.end()[-2], conv.back(), p)) conv.pop_back();
			conv.emplace_back(p);
		}
		// for(const auto &p : conv) fprintf(stderr, "(%d, %d) ", p.x, p.y);
		// fprintf(stderr, "\n");
	}
	double at(const Point &x, const Point &y, int x0) const {
		double k = (double)(y.y - x.y) / (y.x - x.x);
		double b = y.y - k * y.x;
		return k * x0 + b;
	}
	bool check(int x, int y) const {
		if(x < conv.front().x || x > conv.back().x) return false;
		if(x == conv.back().x) return type ? (y <= conv.back().y + eps) : (y >= conv.back().y - eps);
		int l = 1, r = (int)conv.size() - 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(conv[mid].x < x) l = mid + 1;
			else r = mid;
		}
		double vy = at(conv[l - 1], conv[l], x);
		return type ? (y <= vy + eps) : (y >= vy - eps);
	}
} cvu, cvd;

int main() {
#ifndef DEBUG
	freopen("socialdarwin.in", "r", stdin);
	freopen("socialdarwin.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		std::vector<Point> points;
		for(int i = 1; i <= n; i++) { int x, y; scanf("%d%d", &x, &y); points.push_back({x, y}); }
		cvu.construct(points, true), cvd.construct(points, false);
		scanf("%d", &m);
		for(int i = 1; i <= m; i++) scanf("%d%d%d", &q[i].x, &q[i].y, &q[i].r), q[i].id = i;
		
	}
	return 0;
} /*
1
8
1 10
1 -10
10 1`
8 -5
-10 0
8 6
-4 8
-6 8
15
2 -1 3
8 -1 6
-7 -10 2
-10 -1 4
7 10 10
-1 -7 9
-5 0 5
-5 5 4
10 -7 4
-5 5 1
2 1 6
10 3 7
-2 0 3
-2 0 7
-9 -6 6
*/