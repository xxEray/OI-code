#include <bits/stdc++.h>

typedef long long LL;
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
	bool on(const Convex<T> &) const;
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
template<typename T> Vector<T> operator+(const Vector<T> &p) { return p; }
template<typename T> Vector<T> operator-(const Vector<T> &p) { return Vector<T>::from_point(-p.x, -p.y); }
template<typename T> Vector<T> operator+(const Vector<T> &p, const Vector<T> &q) { return Vector<T>::from_point(p.x + q.x, p.y + q.y); }
template<typename T> Vector<T> operator-(const Point<T> &p, const Point<T> &q) { return Vector<T>(q, p); }
template<typename T> Vector<T> operator*(const Vector<T> &p, const T &v) { return Vector<T>::from_point(p.x * v, p.y * v); }
template<typename T> Vector<T> operator*(const T &v, const Vector<T> &p) { return Vector<T>::from_point(p.x * v, p.y * v); }
template<typename T> Vector<double> operator/(const Vector<T> &p, const double &v) { return Vector<double>(Point<double>(p.x / v, p.y / v)); }
template<typename T> T dot(const Vector<T> &p, const Vector<T> &q) { return p.x * q.x + p.y * q.y; }
template<typename T> T cross(const Vector<T> &p, const Vector<T> &q) { return p.x * q.y - p.y * q.x; }
template<typename T> bool parallel(const Vector<T> &p, const Vector<T> &q) { return eq(cross(p, q), (T)0); }
template<typename T> bool same_direction(const Vector<T> &p, const Vector<T> &q) { return parallel(p, q) && !lt(dot(p, q), (T)0); }
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
	T diameter_sq() const;
	double diameter() const { return sqrt(diameter_sq()); }
	template<typename TFunc> void rotating_calipers(TFunc) const;
	int size() const { return up.size() + dn.size() - (up.front() == dn.front()) - (up.back() == dn.back() && up.size() > 1); }
	Point<T> &at(int);
	const Point<T> &at(int) const;
	Point<T> &operator[](int x) { return at(x); }
	const Point<T> &operator[](int x) const { return at(x); }
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
template<typename T> Convex<T>::Convex(std::vector<Point<T>> pts) {
	geometry_assert(!pts.empty());
	auto cmp = [&](const Point<T> &x, const Point<T> &y) { return eq(x.x, y.x) ? lt(x.y, y.y) : lt(x.x, y.x); };
	if(!std::is_sorted(pts.begin(), pts.end(), cmp)) std::sort(pts.begin(), pts.end(), cmp);
	for(int i = 0; i < (int)pts.size(); i++) {
		if(i && eq(pts[i - 1].x, pts[i].x)) up.pop_back();
		const auto &p = pts[i];
		while(up.size() >= 2 && !lt(cross(Vector<T>(up.end()[-2], up.back()), Vector<T>(up.back(), p)), (T)0)) up.pop_back();
		up.emplace_back(p);
	}
	for(int i = 0; i < (int)pts.size(); i++) {
		if(i && eq(pts[i - 1].x, pts[i].x)) continue;
		const auto &p = pts[i];
		while(dn.size() >= 2 && !gt(cross(Vector<T>(dn.end()[-2], dn.back()), Vector<T>(dn.back(), p)), (T)0)) dn.pop_back();
		dn.emplace_back(p);
	}
}
template<typename T> Point<T> &Convex<T>::at(int x) {
	geometry_assert(x < size());
	if(x < (int)up.size()) return up.rbegin()[x];
	else return dn[x - (int)up.size() + (up.front() == dn.front())];
}
template<typename T> const Point<T> &Convex<T>::at(int x) const {
	geometry_assert(x < size());
	if(x < (int)up.size()) return up.rbegin()[x];
	else return dn[x - (int)up.size() + (up.front() == dn.front())];
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
template<typename T> bool Point<T>::on(const Convex<T> &convex) const {
	int i = std::upper_bound(convex.up.begin(), convex.up.end(), x, [&](const T &p, const Point<T> &q) { return p < q.x; }) - convex.up.begin();
	if(i == (int)convex.up.size());
	else if(!i || eq(side(Line<T>(convex.up[i - 1], convex.up[i])), (T)0)) return true;
	i = std::upper_bound(convex.dn.begin(), convex.dn.end(), x, [&](const T &p, const Point<T> &q) { return p < q.x; }) - convex.dn.begin();
	if(i == (int)convex.dn.size());
	else if(!i || eq(side(Line<T>(convex.dn[i - 1], convex.dn[i])), (T)0)) return true;
	if(*this == convex.up.back()) return true;
	if(convex.up.front() != convex.dn.front() && eq(side(Line<T>(convex.up.front(), convex.dn.front())), (T)0)) return true;
	if(convex.up.back() != convex.dn.back() && eq(side(Line<T>(convex.up.back(), convex.dn.back())), (T)0)) return true;
	return false;
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
template<typename T> std::pair<Line<T>, Line<T>> Point<T>::tangent(const Convex<T> &convex) const {
	geometry_assert(!in(convex));
	auto maxx = convex.up.back();
	std::pair<Line<T>, Line<T>> ret;
	if(gt(x, maxx.x)) {
		int l = 0, r = (int)convex.up.size() - 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(!lt(convex.up[mid + 1].side(Line<T>(*this, convex.up[mid])), (T)0)) r = mid;
			else l = mid + 1;
		}
		ret.first = Line<T>(*this, convex.up[l]);
		l = 0, r = (int)convex.dn.size() - 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(!gt(convex.dn[mid + 1].side(Line<T>(*this, convex.dn[mid])), (T)0)) r = mid;
			else l = mid + 1;
		}
		ret.second = Line<T>(*this, convex.dn[l]);
	} else {
		int l = 1, r = convex.size();
		while(l < r) {
			int mid = (l + r) >> 1;
			if(gt(cross(Vector<T>(maxx, *this), Vector<T>(maxx, convex[mid])), (T)0)) r = mid;
			else l = mid + 1;
		}
		int p = l;
		l = 0, r = p - 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(gt(convex[mid + 1].side(Line<T>(*this, convex[mid])), (T)0)) l = mid + 1;
			else r = mid;
		}
		ret.first = Line<T>(*this, convex[l]);
		l = p, r = convex.size() - 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(lt(convex[mid + 1].side(Line<T>(*this, convex[mid])), (T)0)) l = mid + 1;
			else r = mid;
		}
		ret.second = Line<T>(*this, p == convex.size() ? maxx : convex[l]);
	}
	if(lt(cross(ret.first.c, ret.second.c), (T)0)) std::swap(ret.first, ret.second);
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
template<typename T> T Convex<T>::diameter_sq() const {
	if(size() == 1) return 0;
	else if(size() == 2) return edis_sq(up.front(), up.back());
	int j = 2, sz = size();
	T mx = 0;
	auto nxt = [&](int i) { return i + 1 == sz ? 0 : i + 1; };
	for(int i = 0; i < sz; i++) {
		while(!gt(cross(Vector<T>(at(i), at(j)), Vector<T>(at(nxt(i)), at(j))), cross(Vector<T>(at(i), at(nxt(j))), Vector<T>(at(nxt(i)), at(nxt(j)))))) j = nxt(j);
		if(lt(mx, edis_sq(at(i), at(j)))) mx = edis_sq(at(i), at(j));
		if(lt(mx, edis_sq(at(nxt(i)), at(j)))) mx = edis_sq(at(nxt(i)), at(j));
	}
	return mx;
}
template<typename T> template<typename TFunc> void Convex<T>::rotating_calipers(TFunc func) const {
	if(size() == 1) { func(0, 0, 0); return; }
	else if(size() == 2) { func(0, 1, 0), func(0, 1, 1); return; }
	int j = 2, sz = size();
	auto nxt = [&](int i) { return i + 1 == sz ? 0 : i + 1; };
	for(int i = 0; i < sz; i++) {
		while(!gt(cross(Vector<T>(at(i), at(j)), Vector<T>(at(nxt(i)), at(j))), cross(Vector<T>(at(i), at(nxt(j))), Vector<T>(at(nxt(i)), at(nxt(j)))))) j = nxt(j);
		func(i, nxt(i), j);
	}
}
template<typename T> double distance(const Point<T> &p, const Line<T> &q) { return std::abs(cross(Vector<T>(q.p, p), q.c)) / q.c.length(); }
template<typename T> T distance(const Point<T> &p, const Line<T> &q, T &d_sq) { d_sq = q.c.length_sq(); return std::abs(cross(Vector<T>(q.p, p), q.c)); }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		LL A, B;
		scanf("%lld%lld", &A, &B);
		Point<LL> x, y, z;
		scanf("%lld%lld%lld%lld%lld%lld", &x.x, &x.y, &y.x, &y.y, &z.x, &z.y);
		if(parallel(x - y, y - z)) {
			LL len = std::max(A, 2 * B);
			if(edis(x, y) <= len && edis(y, z) <= len && edis(x, z) <= len) { puts("YES"); continue; }
		}
		auto solve = [&]() -> bool {
			Line<LL> line(x, y);
			Line<LL> line2(z, Vector<LL>::from_point(line.c.y, -line.c.x));
			auto t = intersect(line, line2);
			using Pd = Point<double>;
			if(edis(t, (Pd)x) <= B + eps && edis(t, (Pd)y) <= B + eps && edis(t, (Pd)z) <= A + eps) return true;
			if(same_direction(Vector<double>(t, (Pd)x), Vector<double>(t, (Pd)y)) && edis(t, (Pd)x) <= A + eps && edis(t, (Pd)y) <= A + eps && edis(t, (Pd)z) <= B + eps) return true;
			return false;
		};
		// x y z
		if(solve()) { puts("YES"); continue; }
		// x z y
		std::swap(y, z);
		if(solve()) { puts("YES"); continue; }
		// y z x
		std::swap(x, z);
		if(solve()) { puts("YES"); continue; }
		puts("NO");
	}
	return 0;
} /*
1
4 6
0 1
-9 1
-5 -1
*/