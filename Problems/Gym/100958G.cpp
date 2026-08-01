#include <bits/stdc++.h>

typedef long long LL;

const int N = 1000 + 5;

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

bool check(int id) {
	if(id > 1) {
		Vector now(a[id], a[1]);
		for(int i = 2; i < id; i++) if(cross(now, Vector(a[id], a[i])) > 0) now = Vector(a[id], a[i]);
		for(int i = 1; i < id; i++) if(cross(now, Vector(a[id], a[i])) > 0) return false;
	}
	if(id < n) {
		Vector now(a[id], a[n]);
		for(int i = n - 1; i > id; i--) if(cross(now, Vector(a[id], a[i])) > 0) now = Vector(a[id], a[i]);
		for(int i = n; i > id; i--) if(cross(now, Vector(a[id], a[i])) > 0) return false;
	}
	return true;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	for(int i = 1; i <= n; i++) if(!check(i)) { puts("Impossible"); return 0; }
	puts("Possible");
	return 0;
}