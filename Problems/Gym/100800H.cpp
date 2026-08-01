#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const double pi = 3.1415926535897932384626;

int n;

struct Point {
	int x, y;
	Point() : x(0), y(0) {}
	Point(int x_, int y_) : x(x_), y(y_) {}
};
struct Vector {
	int x, y;
	Vector() : x(0), y(0) {}
	Vector(int x_, int y_) : x(x_), y(y_) {}
	Vector(const Point &p, const Point &q) : x(q.x - p.x), y(q.y - p.y) {}
	explicit Vector(const Point &p) : x(p.x), y(p.y) {}
	explicit operator Point() { return Point(x, y); }
	double theta() const { return atan2(y, x); }
};
Vector operator-(const Point &p, const Point &q) { return Vector(q, p); }
LL dot(const Vector &p, const Vector &q) { return (LL)p.x * q.x + (LL)p.y * q.y; }
LL cross(const Vector &p, const Vector &q) { return (LL)p.x * q.y - (LL)p.y * q.x; }

Point a[N];
double angl[N], angr[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	std::vector<int> q;
	for(int i = 1; i <= n; i++) {
		while(q.size() >= 2 && cross(Vector(a[q.end()[-2]], a[q.back()]), Vector(a[q.back()], a[i])) >= 0) q.pop_back();
		angl[i] = q.empty() ? pi : Vector(a[i], a[q.back()]).theta();
		if(angl[i] < 0) angl[i] = pi;
		q.emplace_back(i);
	}
	// printf("q: "); for(int x : q) printf("%d ", x); puts("");
	// printf("angl: "); for(int i = 1; i <= n; i++) printf("%.5f ", angl[i]); puts("");
	q.clear();
	for(int i = n; i >= 1; i--) {
		while(q.size() >= 2 && cross(Vector(a[q.end()[-2]], a[q.back()]), Vector(a[q.back()], a[i])) <= 0) q.pop_back();
		angr[i] = q.empty() ? 0 : Vector(a[i], a[q.back()]).theta();
		if(angr[i] < 0) angr[i] = 0;
		q.emplace_back(i);
	}
	// printf("q: "); for(int x : q) printf("%d ", x); puts("");
	// printf("angr: "); for(int i = 1; i <= n; i++) printf("%.5f ", angr[i]); puts("");
	for(int i = 1; i <= n; i++) printf("%.5f\n", (angl[i] - angr[i]) / pi * 12);
	return 0;
}