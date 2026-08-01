#include <bits/stdc++.h>

typedef long long LL;

const int N = 2.5e5 + 5;

int n, K;

struct Point {
	int x, y;
	Point() : x(0), y(0) {}
	Point(int x_, int y_) : x(x_), y(y_) {}
};
bool operator==(const Point &x, const Point &y) { return x.x == y.x && x.y == y.y; }
bool operator!=(const Point &x, const Point &y) { return x.x != y.x || x.y != y.y; }
LL edis_sq(const Point &x, const Point &y) { return (LL)(x.x - y.x) * (x.x - y.x) + (LL)(x.y - y.y) * (x.y - y.y); }
double edis(const Point &x, const Point &y) { return sqrt(edis_sq(x, y)); }
struct Vector {
	int x, y;
	Vector() : x(0), y(0) {}
	Vector(const Point &p, const Point &q) : x(q.x - p.x), y(q.y - p.y) {}
	explicit Vector(const Point &p) : x(p.x), y(p.y) {}
	explicit operator Point() { return Point(x, y); }
	double theta() const { return atan2(y, x); }
};
bool operator==(const Vector &x, const Vector &y) { return x.x == y.x && x.y == y.y; }
bool operator!=(const Vector &x, const Vector &y) { return x.x != y.x || x.y != y.y; }
Vector operator-(const Point &p, const Point &q) { return Vector(q, p); }
LL dot(const Vector &p, const Vector &q) { return (LL)p.x * q.x + (LL)p.y * q.y; }
LL cross(const Vector &p, const Vector &q) { return (LL)p.x * q.y - (LL)p.y * q.x; }

Point a[N];

LL get_diameter(int l, int r) {
	std::vector<Point> cvu, cvd;
	for(int i = l; i <= r; i++) {
		while(cvu.size() >= 2 && cross(Vector(cvu.end()[-2], cvu.back()), Vector(cvu.back(), a[i])) >= 0) cvu.pop_back();
		cvu.emplace_back(a[i]);
		while(cvd.size() >= 2 && cross(Vector(cvd.end()[-2], cvd.back()), Vector(cvd.back(), a[i])) <= 0) cvd.pop_back();
		cvd.emplace_back(a[i]);
	}
	std::vector<Point> convex;
	convex.insert(convex.end(), cvu.begin(), cvu.end()), convex.insert(convex.end(), cvd.rbegin() + (cvd.back() == cvu.back()), cvd.rend());
	if(convex.front() == convex.back()) convex.pop_back();
	int sz = convex.size();
	if(sz == 1) return 0;
	else if(sz == 2) return edis_sq(convex[0], convex[1]);
	convex.emplace_back(convex.front());
	int j = 2;
	LL mx = 0;
	for(int i = 0; i < sz; i++) {
		while(std::abs(cross(Vector(convex[i], convex[j]), Vector(convex[i + 1], convex[j]))) <= std::abs(cross(Vector(convex[i], convex[(j + 1) % sz]), Vector(convex[i + 1], convex[(j + 1) % sz]))))
			j = (j + 1) % sz;
		mx = std::max({mx, edis_sq(convex[i], convex[j]), edis_sq(convex[i + 1], convex[j])});
	}
	return mx;
}

bool check(LL x) {
	// printf("check(%lld)\n", x);
	int cnt = 0;
	int l = 1;
	while(l <= n) {
		cnt++;
		int r = -1, ku = 0;
		for(int k = 0; k <= 20; k++)
			if(get_diameter(l, std::min(l + (1 << k), n)) <= x) {
				if(l + (1 << k) >= n) { r = n; break; }
			} else { r = l + (k ? (1 << (k - 1)) - 1 : 0), ku = k - 1; break; }
		assert(r != -1);
		if(r == n) break;
		for(int k = ku; k >= 0; k--) if(r + (1 << k) <= n && get_diameter(l, r + (1 << k)) <= x) r = r + (1 << k);
		if(r < n && a[r].x == a[r + 1].x) {
			int xx = a[r].x;
			while(r >= l && a[r].x == xx) r--;
			if(r < l) return false;
		}
		// printf("[%d, %d]\n", l, r);
		l = r + 1;
	}
	return cnt <= K;
}

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	std::sort(a + 1, a + n + 1, [&](const Point &x, const Point &y) { return x.x == y.x ? x.y < y.y : x.x < y.x; });
	LL l = 0, r = 2e18;
	while(l < r) {
		LL mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%lld\n", l);
	return 0;
}