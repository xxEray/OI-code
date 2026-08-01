#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int MAXQ = 1e6 + 5;
const double eps = 1e-6;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, Q;

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

Point<LL> a[N];
struct Query { int t, x, y; } qr[MAXQ];

int m;
std::vector<int> b[N], id[N];

std::map<std::pair<int, int>, int> mp;

int ld[2 * MAXQ];
LL sum[2 * MAXQ];
int find(int x) { return x == ld[x] ? x : ld[x] = find(ld[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? ld[x] = y, sum[y] = std::max(sum[x] + sum[y], -LLINF) : 0; }

bool vis[2 * MAXQ];
LL dfs(int u, int v) {
	int iduv = mp[{u, v}];
	if(vis[id[u][iduv]]) return 0;
	// printf("%d -> %d\n", u, v);
	vis[id[u][iduv]] = true;
	int idvu = mp[{v, u}], idvw = (idvu - 1 + b[v].size()) % b[v].size();
	int w = b[v][idvw];
	merge(id[u][iduv], id[v][idvw]);
	return dfs(v, w) + cross((Vector<LL>)a[u], (Vector<LL>)a[v]);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].x, &a[i].y);
	scanf("%d", &Q);
	for(int i = 1; i <= Q; i++) {
		scanf("%d%d%d", &qr[i].t, &qr[i].x, &qr[i].y);
		qr[i].x++, qr[i].y++;
		if(qr[i].t == 1) b[qr[i].x].emplace_back(qr[i].y), b[qr[i].y].emplace_back(qr[i].x);
	}
	for(int i = 1; i <= n; i++) {
		std::sort(b[i].begin(), b[i].end(), [&](int x, int y) { return polar_compare(Vector<LL>(a[i], a[x]), Vector<LL>(a[i], a[y])); });
		for(int j = 0; j < (int)b[i].size(); j++) mp[{i, b[i][j]}] = j;
		id[i].resize(b[i].size());
		for(auto &v : id[i]) v = ++m;
	}
	// for(int i = 1; i <= n; i++) {
	// 	printf("b[%d]: ", i);
	// 	for(int j : b[i]) printf("%d ", j);
	// 	puts("");
	// }
	for(int i = 1; i <= m; i++) ld[i] = i;
	for(int u = 1; u <= n; u++)
		for(int i = 0; i < (int)b[u].size(); i++) {
			int v = b[u][i];
			if(!vis[id[u][i]]) {
				LL val = dfs(u, v);
				// printf("val = %lld\n", val);
				sum[find(id[u][i])] = (val <= 0 ? -LLINF : val);
			}
		}
	std::vector<LL> ans;
	for(int i = Q; i >= 1; i--) {
		int u = qr[i].x, v = qr[i].y;
		if(qr[i].t == 1) {
			merge(id[u][mp[{u, v}]], id[v][mp[{v, u}]]);
		} else {
			ans.emplace_back(sum[find(id[u][mp[{u, v}]])]);
		}
	}
	std::reverse(ans.begin(), ans.end());
	for(auto v : ans) printf("%lld\n", v <= 0 ? -1LL : v);
	return 0;
}