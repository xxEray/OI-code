#include <bits/stdc++.h>

const int N = 50 + 5;

int n;
char s[N];

typedef long long LL;
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
bool vis[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	scanf("%s", s + 1);
	int st = 0;
	for(int i = 1; i <= n; i++) if(st == 0 || a[st].x > a[i].x) st = i;
	std::vector<int> ans{st};
	vis[st] = true;
	int last = st;
	for(int si = 1; si < n - 1; si++) {
		char opt = s[si];
		int nxt = 0;
		for(int i = 1; i <= n; i++) if(!vis[i] && i != last) {
			if(nxt == 0) nxt = i;
			else if((cross(Vector(a[last], a[nxt]), Vector(a[last], a[i])) > 0) ^ (opt == 'L')) nxt = i;
		}
		ans.emplace_back(nxt);
		vis[nxt] = true;
		last = nxt;
	}
	for(int i = 1; i <= n; i++) if(!vis[i]) ans.emplace_back(i);
	for(int x : ans) printf("%d ", x);
	return 0;
}