#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e4 + 5;
const double eps = 1e-8;

#ifdef DEBUG
	#define geometry_assert(...) assert(__VA_ARGS__)
#else
	#define geometry_assert(...) ((void)0)
#endif
template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0> inline bool eq(const T &x, const T &y) { return x == y; }
template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0> inline bool lt(const T &x, const T &y) { return x < y; }
template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0> inline bool gt(const T &x, const T &y) { return x > y; }
template<typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0> inline bool eq(const T &x, const T &y) { return std::abs(x - y) <= eps; }
template<typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0> inline bool lt(const T &x, const T &y) { return x < y - eps; }
template<typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0> inline bool gt(const T &x, const T &y) { return x > y + eps; }
template<typename T> struct Point;
template<typename T> struct Vector;
template<typename T> struct Line;
template<typename T> struct Point {
	T x, y;
	Point() : x(), y() {}
	Point(T x_, T y_) : x(x_), y(y_) {}
	template<typename T2> explicit Point(const Point<T2> &p) : x(p.x), y(p.y) {}
	static Point origin() { return Point(); }
	bool on(const Line<T> &) const;
	T side(const Line<T> &) const;
};
template<typename T> bool operator==(const Point<T> &x, const Point<T> &y) { return eq(x.x, y.x) && eq(x.y, y.y); }
template<typename T> bool operator!=(const Point<T> &x, const Point<T> &y) { return !eq(x.x, y.x) || !eq(x.y, y.y); }
template<typename T> T edis_sq(const Point<T> &x, const Point<T> &y) { return (x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y); }
template<typename T> double edis(const Point<T> &x, const Point<T> &y) { return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y)); }
template<typename T> struct Vector {
	T x, y;
	Vector() : x(), y() {}
	Vector(const Point<T> &p, const Point<T> &q) : x(q.x - p.x), y(q.y - p.y) {}
	template<typename T2> explicit Vector(const Vector<T2> &p) : x(p.x), y(p.y) {}
	explicit Vector(const Point<T> &p) : x(p.x), y(p.y) {}
	explicit operator Point<T>() { return Point<T>(x, y); }
	static Vector origin() { return Vector(); }
	double length() const { return sqrt(x * x + y * y); }
	T length_sq() const { return x * x + y * y; }
	double angle() const { return atan2(y, x); }
};
template<typename T> bool operator==(const Vector<T> &x, const Vector<T> &y) { return eq(x.x, y.x) && eq(x.y, y.y); }
template<typename T> bool operator!=(const Vector<T> &x, const Vector<T> &y) { return !eq(x.x, y.x) || !eq(x.y, y.y); }
template<typename T> Point<T> operator+(const Point<T> &p, const Vector<T> &q) { return Point<T>(p.x + q.x, p.y + q.y); }
template<typename T> Point<T> operator+(const Vector<T> &q, const Point<T> &p) { return Point<T>(p.x + q.x, p.y + q.y); }
template<typename T> Vector<T> operator+(const Vector<T> &p, const Vector<T> &q) { return Vector<T>(Point<T>(p.x + q.x, p.y + q.y)); }
template<typename T> Vector<T> operator-(const Point<T> &p, const Point<T> &q) { return Vector<T>(q, p); }
template<typename T> Vector<T> operator*(const Vector<T> &p, const T &v) { return Vector<T>(Point<T>(p.x * v, p.y * v)); }
template<typename T> Vector<T> operator*(const T &v, const Vector<T> &p) { return Vector<T>(Point<T>(p.x * v, p.y * v)); }
template<typename T> Vector<double> operator/(const Vector<T> &p, const double &v) { return Vector<double>(Point<double>(p.x / v, p.y / v)); }
template<typename T> T dot(const Vector<T> &p, const Vector<T> &q) { return p.x * q.x + p.y * q.y; }
template<typename T> T cross(const Vector<T> &p, const Vector<T> &q) { return p.x * q.y - p.y * q.x; }
template<typename T> bool parallel(const Vector<T> &p, const Vector<T> &q) { return eq(cross(p, q), (T)0); }
template<typename T> bool same_direction(const Vector<T> &p, const Vector<T> &q) { return parallel(p, q) && gt(p.x, (T)0) == gt(q.x, (T)0); }
template<typename T> bool perp(const Vector<T> &p, const Vector<T> &q) { return eq(dot(p.c, q.c), (T)0); }
template<typename T> bool polar_compare(const Vector<T> &p, const Vector<T> &q) {
	geometry_assert(p != Vector<T>::origin() && q != Vector<T>::origin());
	auto is_lower = [&](const Vector<T> &x) { return lt(x.y, (T)0) || (eq(x.y, (T)0) && lt(x.x, (T)0)); };
	return is_lower(p) == is_lower(q) ? gt(cross(p, q), (T)0) : is_lower(p) < is_lower(q);
}
template<typename T> struct Line {
	Point<T> p;
	Vector<T> c;
	Line() : p(), c(Point<T>(1, 0)) {}
	Line(const Point<T> &x, const Vector<T> &y) : p(x), c(y) { geometry_assert(y != Vector<T>::origin()); }
	Line(const Point<T> &x, const Point<T> &y) : p(x), c(y - x) { geometry_assert(!eq(c.x, (T)0) || !eq(c.y, (T)0)); }
	template<typename T2> explicit Line(const Line<T2> &x) : p(x.p), c(x.c) {}
};
template<typename T> T Point<T>::side(const Line<T> &p) const { return cross(p.c, Vector<T>(p.p, *this)); }
template<typename T> bool Point<T>::on(const Line<T> &p) const { return eq(cross(p.c, Vector<T>(p.p, *this)), (T)0); }
template<typename T> bool parallel(const Line<T> &p, const Line<T> &q) { return parallel(p.c, q.c); }
template<typename T> bool same_direction(const Line<T> &p, const Line<T> &q) { return same_direction(p.c, q.c); }
template<typename T> bool perp(const Line<T> &p, const Line<T> &q) { return perp(p.c, q.c); }
template<typename T> bool overlap(const Line<T> &p, const Line<T> &q) { return eq(cross(p.c, q.c), (T)0) && p.p.on(q); }
template<typename T> Point<double> intersect(const Line<T> &x, const Line<T> &y) {
	geometry_assert(!parallel(x, y));
	double s1 = cross((y.p + y.c) - x.p, y.p - x.p), s2 = cross(y.p - (x.p + x.c), (y.p + y.c) - (x.p + x.c));
	return (Point<double>)x.p + x.c / (s1 + s2) * s1;
}

int n;
Point<LL> a[N];

bool on_right(const Line<LL> &x, const Line<LL> &y, const Line<LL> &p) {
	geometry_assert(!parallel(x, y));
	LL s1 = cross((y.p + y.c) - x.p, y.p - x.p), s2 = cross(y.p - (x.p + x.c), (y.p + y.c) - (x.p + x.c));
	Vector<LL> r = (Vector<LL>)x.p * (s1 + s2) + x.c * s1;
	auto cross_int128 = [&](const Vector<LL> &u, const Vector<LL> &v) { return (__int128_t)u.x * v.y - (__int128_t)u.y * v.x; };
	return cross_int128(p.c * (s1 + s2), Vector<LL>(Point<LL>(r.x - p.p.x * (s1 + s2), r.y - p.p.y * (s1 + s2)))) <= 0;
}

bool check(int d) {
	std::vector<Line<LL>> vct;
	for(int i = 1; i <= n; i++) {
		int i_ = i + d + 1;
		if(i_ > n) i_ -= n;
		vct.emplace_back(a[i_], a[i]);
	}
	std::sort(vct.begin(), vct.end(), [&](const Line<LL> &x, const Line<LL> &y) { return polar_compare(x.c, y.c); });
	// printf("check(%d):\nvct:\n", d); for(auto p : vct) printf("  (%lld, %lld) (%lld, %lld) [(%lld, %lld)]\n", p.p.x, p.p.y, (p.p + p.c).x, (p.p + p.c).y, p.c.x, p.c.y); puts("");
	// assert(vct.size() >= 2);
	std::deque<Line<LL>> ret;
	for(auto p : vct) {
		while(ret.size() >= 2) {
			if(overlap(ret.end()[-2], ret.back())) return false;
			else if(on_right(ret.end()[-2], ret.back(), p)) ret.pop_back();
			else break;
		}
		while(ret.size() >= 2) {
			if(overlap(ret[0], ret[1])) return false;
			else if(on_right(ret[0], ret[1], p)) ret.pop_front();
			else break;
		}
		ret.emplace_back(p);
	}
	while(ret.size() >= 2) {
		if(overlap(ret.end()[-2], ret.back())) return false;
		else if(on_right(ret.end()[-2], ret.back(), ret[0])) ret.pop_back();
		else break;
	}
	// printf(" ret:\n"); for(auto p : ret) printf("  (%lld, %lld) (%lld, %lld) [(%lld, %lld)]\n", p.p.x, p.p.y, (p.p + p.c).x, (p.p + p.c).y, p.c.x, p.c.y); puts("");
	return ret.size() > 2;
}

int main() {
#ifndef DEBUG
	freopen("jungle.in", "r", stdin);
	freopen("jungle.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].x, &a[i].y);
	int l = 0, r = n / 2;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(check(mid)) l = mid + 1;
		else r = mid;
	}
	printf("%d\n", l);
	return 0;
}