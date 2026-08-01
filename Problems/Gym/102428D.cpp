#include <bits/stdc++.h>

typedef long long LL;

const int N = 1000 + 5;
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
template<typename T> struct Convex;
template<typename T> struct Point {
	T x, y;
	Point() : x(), y() {}
	Point(T x_, T y_) : x(x_), y(y_) {}
	template<typename T2> explicit Point(const Point<T2> &p) : x(p.x), y(p.y) {}
	static Point origin() { return Point(); }
	bool in(const Convex<T> &) const;
	bool strictly_in(const Convex<T> &) const;
	std::pair<Line<T>, Line<T>> tangent(const Convex<T> &) const;
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
	static Vector<T> from_point(const T &x, const T &y) { return Vector<T>(x, y); }
private:
	explicit Vector(const T &x_, const T &y_) : x(x_), y(y_) {}
};
template<typename T> bool operator==(const Vector<T> &x, const Vector<T> &y) { return eq(x.x, y.x) && eq(x.y, y.y); }
template<typename T> bool operator!=(const Vector<T> &x, const Vector<T> &y) { return !eq(x.x, y.x) || !eq(x.y, y.y); }
template<typename T> Point<T> operator+(const Point<T> &p, const Vector<T> &q) { return Point<T>(p.x + q.x, p.y + q.y); }
template<typename T> Point<T> operator+(const Vector<T> &q, const Point<T> &p) { return Point<T>(p.x + q.x, p.y + q.y); }
template<typename T> Vector<T> operator+(const Vector<T> &p, const Vector<T> &q) { return Vector<T>::from_point(p.x + q.x, p.y + q.y); }
template<typename T> Vector<T> operator-(const Point<T> &p, const Point<T> &q) { return Vector<T>(q, p); }
template<typename T> Vector<T> operator*(const Vector<T> &p, const T &v) { return Vector<T>::from_point(p.x * v, p.y * v); }
template<typename T> Vector<T> operator*(const T &v, const Vector<T> &p) { return Vector<T>::from_point(p.x * v, p.y * v); }
template<typename T> Vector<double> operator/(const Vector<T> &p, const double &v) { return Vector<double>(Point<double>(p.x / v, p.y / v)); }
template<typename T> T dot(const Vector<T> &p, const Vector<T> &q) { return p.x * q.x + p.y * q.y; }
template<typename T> T cross(const Vector<T> &p, const Vector<T> &q) { return p.x * q.y - p.y * q.x; }
template<typename T> bool parallel(const Vector<T> &p, const Vector<T> &q) { return eq(cross(p, q), (T)0); }
template<typename T> bool same_direction(const Vector<T> &p, const Vector<T> &q) { return parallel(p, q) && (eq(p.x, (T)0) ? gt(p.y, (T)0) == gt(q.y, (T)0) : gt(p.x, (T)0) == gt(q.x, (T)0)); }
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
template<typename T> struct Convex {
	std::vector<Point<T>> up, dn;
	Convex() : up({Point<T>()}), dn({Point<T>()}) {}
	Convex(std::vector<Point<T>>);
	static Convex<T> from_convex(const std::vector<Point<T>> &);
	std::vector<Point<T>> upper_convex() const { return up; }
	std::vector<Point<T>> lower_convex() const { return dn; }
	std::vector<Point<T>> full_convex() const;
};
template<typename T> bool operator==(const Convex<T> &x, const Convex<T> &y) { return x.up == y.up && x.dn == y.dn; }
template<typename T> bool operator!=(const Convex<T> &x, const Convex<T> &y) { return x.up != y.up || x.dn != y.dn; }
template<typename T> std::vector<Point<T>> Convex<T>::full_convex() const {
	std::vector<Point<T>> ret(up.rbegin(), up.rend());
	ret.insert(ret.end(), dn.begin() + (up.front() == dn.front()), dn.end());
	if(ret.size() >= 2 && ret.front() == ret.back()) ret.pop_back();
	return ret;
}
template<typename T> Convex<T> Convex<T>::from_convex(const std::vector<Point<T>> &vct) {
	geometry_assert(!vct.empty());
	Convex<T> ret;
	int p = 0;
	for(int i = 0; i < (int)vct.size(); i++) if(lt(vct[i].x, vct[p].x)) p = i;
	ret.up = std::vector<Point<T>>(vct.begin(), vct.begin() + p + 1);
	while(p + 1 < (int)vct.size() && eq(vct[p].x, vct[p + 1].x)) p++;
	ret.dn = std::vector<Point<T>>(vct.begin() + p, vct.end());
	std::reverse(ret.up.begin(), ret.up.end());
	if(ret.dn.empty() || !eq(ret.dn.back().x, vct.front().x)) ret.dn.emplace_back(vct.front());
	geometry_assert(ret == Convex<T>(vct));
	return ret;
}
template<typename T> Convex<T>::Convex(std::vector<Point<T>> vct) {
	geometry_assert(!vct.empty());
	auto cmp = [&](const Point<T> &x, const Point<T> &y) { return eq(x.x, y.x) ? lt(x.y, y.y) : lt(x.x, y.x); };
	if(!std::is_sorted(vct.begin(), vct.end(), cmp)) std::sort(vct.begin(), vct.end(), cmp);
	for(int i = 0; i < (int)vct.size(); i++) {
		if(i && eq(vct[i - 1].x, vct[i].x)) up.pop_back();
		const auto &p = vct[i];
		while(up.size() >= 2 && !lt(cross(Vector<T>(up.end()[-2], up.back()), Vector<T>(up.back(), p)), (T)0)) up.pop_back();
		up.emplace_back(p);
	}
	for(int i = 0; i < (int)vct.size(); i++) {
		if(i && eq(vct[i - 1].x, vct[i].x)) continue;
		const auto &p = vct[i];
		while(dn.size() >= 2 && !gt(cross(Vector<T>(dn.end()[-2], dn.back()), Vector<T>(dn.back(), p)), (T)0)) dn.pop_back();
		dn.emplace_back(p);
	}
}
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
template<typename T> Point<T> intersect(const Line<T> &x, const Line<T> &y, T &d) {
	geometry_assert(!parallel(x, y));
	T s1 = cross((y.p + y.c) - x.p, y.p - x.p), s2 = cross(y.p - (x.p + x.c), (y.p + y.c) - (x.p + x.c));
	d = s1 + s2;
	return (Vector<T>)x.p * (s1 + s2) + x.c * s1;
}
template<typename T> bool Point<T>::in(const Convex<T> &convex) const {
	int i = std::upper_bound(convex.up.begin(), convex.up.end(), x, [&](const T &p, const Point<T> &q) { return p < q.x; }) - convex.up.begin();
	if(i == (int)convex.up.size()) { if(gt(x, convex.up.back().x) || gt(y, convex.up.back().y)) return false; }
	else if(!i || gt(side(Line<T>(convex.up[i - 1], convex.up[i])), (T)0)) return false;
	i = std::upper_bound(convex.dn.begin(), convex.dn.end(), x, [&](const T &p, const Point<T> &q) { return p < q.x; }) - convex.dn.begin();
	if(i == (int)convex.dn.size()) { if(gt(x, convex.dn.back().x) || lt(y, convex.dn.back().y)) return false; }
	else if(!i || lt(side(Line<T>(convex.dn[i - 1], convex.dn[i])), (T)0)) return false;
	return true;
}
template<typename T> bool Point<T>::strictly_in(const Convex<T> &convex) const {
	int i = std::upper_bound(convex.up.begin(), convex.up.end(), x, [&](const T &p, const Point<T> &q) { return p < q.x; }) - convex.up.begin();
	if(i == (int)convex.up.size()) return false;
	else if(!i || !lt(side(Line<T>(convex.up[i - 1], convex.up[i])), (T)0)) return false;
	i = std::upper_bound(convex.dn.begin(), convex.dn.end(), x, [&](const T &p, const Point<T> &q) { return p < q.x; }) - convex.dn.begin();
	if(i == (int)convex.dn.size()) return false;
	else if(!i || !gt(side(Line<T>(convex.dn[i - 1], convex.dn[i])), (T)0)) return false;
	return true;
}
template<typename T> std::pair<Line<T>, Line<T>> Point<T>::tangent(const Convex<T> &convex) const { // to be checked
	geometry_assert(!in(convex));
	T mnx = convex.front().x, mxx = convex.front().x;
	for(auto [t, _] : convex.full_convex()) {
		if(lt(t, mnx)) mnx = t;
		if(gt(t, mxx)) mxx = t;
	}
	T pivot;
	if(lt(x, mnx) || gt(x, mxx)) {
		T mn = mxx;
		for(auto p : convex) if(x <= mn) mn = p.x, pivot = p.y;
	} else pivot = y;
	std::vector<Point<T>> cvu, cvd;
	for(auto p : convex.full_convex())
		if(y >= pivot) cvu.emplace_back(p.x, p.y);
		else cvd.emplace_back(p.x, p.y);
	std::reverse(cvu.begin(), cvu.end());
	std::pair<Line<T>, Line<T>> ret;
	int l = 0, r = (int)cvd.size() - 1;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(!lt(cross(Vector<T>(*this, cvd[mid]), Vector<T>(cvd[mid], cvd[mid + 1])), 0)) r = mid;
		else l = mid + 1;
	}
	ret.first = Line<T>(*this, cvd[l]);
	l = 0, r = (int)cvu.size() - 1;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(!lt(cross(Vector<T>(cvu[mid], cvu[mid + 1]), Vector<T>(*this, cvu[mid])), 0)) r = mid;
		else l = mid + 1;
	}
	ret.second = Line<T>(*this, cvu[l]);
	return ret;
}
template<typename T> Convex<T> minkowski(const Convex<T> &x, const Convex<T> &y) {
	std::vector<Point<T>> px = x.full_convex(), py = y.full_convex();
	std::vector<Vector<T>> vx, vy;
	for(int i = 0; i < (int)px.size() - 1; i++) vx.emplace_back(Vector<T>(px[i], px[i + 1]));
	vx.emplace_back(Vector<T>(px.back(), px.front()));
	for(int i = 0; i < (int)py.size() - 1; i++) vy.emplace_back(Vector<T>(py[i], py[i + 1]));
	vy.emplace_back(Vector<T>(py.back(), py.front()));
	std::vector<Vector<T>> vz(vx.size() + vy.size());
	std::merge(vx.begin(), vx.end(), vy.begin(), vy.end(), vz.begin(), [&](const Vector<T> &p, const Vector<T> &q) {
		auto is_left = [&](const Vector<T> &t) { return lt(t.x, (T)0) || (eq(t.x, (T)0) && lt(t.y, (T)0)); };
		return is_left(p) == is_left(q) ? gt(cross(p, q), (T)0) : is_left(p) > is_left(q);
	});
	std::vector<Point<T>> pz({Point<T>(px.front().x + py.front().x, px.front().y + py.front().y)});
	for(auto p : vz) {
		auto now = pz.back() + p;
		if(pz.size() >= 2 && same_direction(Vector<T>(pz.end()[-2], pz.back()), p)) pz.pop_back();
		pz.emplace_back(now);
	}
	pz.pop_back();
	return Convex<T>::from_convex(pz);
}

int n;
std::pair<int, Point<LL>> a[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld%lld%d", &a[i].second.x, &a[i].second.y, &a[i].first);
	std::vector<std::pair<Vector<LL>, bool>> seq;
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		auto now = a[i].second;
		std::vector<Point<LL>> vct;
		for(int j = 1; j <= n; j++) if(a[j].first > a[i].first) vct.emplace_back(a[j].second);
		if(vct.empty()) continue;
		// printf("i = %d\n", i);
		// for(auto p : vct) printf("(%lld, %lld) ", p.x, p.y);
		// puts("");
		Vector<LL> mostr(now, vct.front());
		for(auto p : vct) if(cross(Vector<LL>(now, p), mostr) > 0) mostr = Vector<LL>(now, p);
		for(auto p : vct) if(cross(Vector<LL>(now, p), mostr) > 0) { puts("N"); return 0; }
		Vector<LL> mostl(now, vct.front());
		for(auto p : vct) if(cross(Vector(now, p), mostl) < 0) mostl = Vector<LL>(now, p);
		Vector<LL> l = Vector<LL>::from_point(mostl.y, -mostl.x), r = Vector<LL>::from_point(-mostr.y, mostr.x);
		cnt++;
		// printf("l: (%lld, %lld)  r: (%lld, %lld)\n", l.x, l.y, r.x, r.y);
		auto is_upper = [&](const Vector<LL> &p) { return p.y > 0 || (p.y == 0 && p.x > 0); };
		if(!is_upper(l) && is_upper(r)) {
			seq.emplace_back(l, 0);
			seq.emplace_back(Vector<LL>::from_point(1, 0), 0), seq.emplace_back(r, 1);
		} else {
			seq.emplace_back(l, 0);
			seq.emplace_back(r, 1);
		}
	}
	std::sort(seq.begin(), seq.end(), [&](const std::pair<Vector<LL>, bool> &x, const std::pair<Vector<LL>, bool> &y) {
		return same_direction(x.first, y.first) ? x.second < y.second : polar_compare(x.first, y.first);
	});
	// for(auto [p, v] : seq) printf("(%lld, %lld) %d\n", p.x, p.y, v);
	bool flag = false;
	int tot = 0;
	for(int i = 0; i < (int)seq.size(); i++) {
		tot += seq[i].second ? -1 : 1;
		if(i == (int)seq.size() - 1 || !same_direction(seq[i].first, seq[i + 1].first) || seq[i].second != seq[i + 1].second)
			flag |= (tot == cnt);
	}
	puts(cnt == 0 || flag ? "Y" : "N");
	return 0;
} /*
4
-200 -100 5
-100 -200 5
-100 -100 9
-200 -200 9
*/