#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n;
LL S;

struct Point {
	int x, y;
	Point() : x(0), y(0) {}
	Point(int x_, int y_) : x(x_), y(y_) {}
};
bool operator==(const Point &x, const Point &y) { return x.x == y.x && x.y == y.y; }
bool operator!=(const Point &x, const Point &y) { return x.x != y.x || x.y != y.y; }
struct Vector {
	int x, y;
	Vector() : x(0), y(0) {}
	Vector(const Point &p, const Point &q) : x(q.x - p.x), y(q.y - p.y) {}
	explicit Vector(const Point &p) : x(p.x), y(p.y) {}
	explicit operator Point() { return Point(x, y); }
};
bool operator==(const Vector &x, const Vector &y) { return x.x == y.x && x.y == y.y; }
bool operator!=(const Vector &x, const Vector &y) { return x.x != y.x || x.y != y.y; }
Vector operator-(const Point &p, const Point &q) { return Vector(q, p); }
LL dot(const Vector &p, const Vector &q) { return (LL)p.x * q.x + (LL)p.y * q.y; }
LL cross(const Vector &p, const Vector &q) { return (LL)p.x * q.y - (LL)p.y * q.x; }

Point a[N];

LL lv[N], rv[N];

int main() {
	scanf("%d%lld", &n, &S);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	std::sort(a + 1, a + n + 1, [&](const Point &x, const Point &y) { return x.x == y.x ? x.y < y.y : x.x < y.x; });
	std::vector<int> stku, stkd;
	LL val = 0;
	auto calc = [&](std::vector<int> &stk) -> LL {
		if(stk.size() <= 1) return 0;
		return cross(Vector(a[stk.back()]), Vector(a[stk.end()[-2]]));
	};
	for(int i = 1; i <= n; i++) {
		while(stku.size() >= 2 && cross(Vector(a[stku.end()[-2]], a[stku.back()]), Vector(a[stku.back()], a[i])) >= 0) val -= calc(stku), stku.pop_back();
		stku.emplace_back(i), val += calc(stku);
		while(stkd.size() >= 2 && cross(Vector(a[stkd.end()[-2]], a[stkd.back()]), Vector(a[stkd.back()], a[i])) <= 0) val -= -calc(stkd), stkd.pop_back();
		stkd.emplace_back(i), val += -calc(stkd);
		// printf("i = %d:\n", i);
		// printf("  stku: "); for(int x : stku) printf("%d ", x); puts("");
		// printf("  stkd: "); for(int x : stkd) printf("%d ", x); puts("");
		lv[i] = val + cross(Vector(a[stku.front()]), Vector(a[stkd.front()])) + cross(Vector(a[stkd.back()]), Vector(a[stku.back()]));
	}
	stku.clear(), stkd. clear();
	val = 0;
	for(int i = n; i >= 1; i--) {
		while(stku.size() >= 2 && cross(Vector(a[stku.end()[-2]], a[stku.back()]), Vector(a[stku.back()], a[i])) >= 0) val -= calc(stku), stku.pop_back();
		stku.emplace_back(i), val += calc(stku);
		while(stkd.size() >= 2 && cross(Vector(a[stkd.end()[-2]], a[stkd.back()]), Vector(a[stkd.back()], a[i])) <= 0) val -= -calc(stkd), stkd.pop_back();
		stkd.emplace_back(i), val += -calc(stkd);
		// printf("i = %d:\n", i);
		// printf("  stku: "); for(int x : stku) printf("%d ", x); puts("");
		// printf("  stkd: "); for(int x : stkd) printf("%d ", x); puts("");
		rv[i] = val + cross(Vector(a[stku.front()]), Vector(a[stkd.front()])) + cross(Vector(a[stkd.back()]), Vector(a[stku.back()]));
	}
	// printf("lv: "); for(int i = 1; i <= n; i++) printf("%lld ", lv[i]); puts("");
	// printf("rv: "); for(int i = 1; i <= n; i++) printf("%lld ", rv[i]); puts("");
	LL ans = lv[n];
	auto update = [&](LL v) { if(std::abs(v - 2 * S) < std::abs(ans - 2 * S) || (std::abs(v - 2 * S) == std::abs(ans - 2 * S) && v < ans)) ans = v; };
	update(rv[1]);
	for(int i = 1; i < n; i++) if(a[i].x < a[i + 1].x) update(std::abs(lv[i] - rv[i + 1]));
	printf("%.4f\n", ans / 2.);
	return 0;
}