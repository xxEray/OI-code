#include <cstdio>
#include <algorithm>
#include <deque>

typedef long long LL;

const int N = 2e5 + 5;

LL a[N], b[N];
int n;

LL f[N];

struct Point {
	LL x, y;
	Point() = default;
	Point(LL x_, LL y_) : x(x_), y(y_) {}
};
std::deque<Point> q;

inline long double slope(Point i, Point j) { return (long double)(i.y - j.y) / (i.x - j.x); }

int main() {
	scanf("%d%lld", &n, &b[0]);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	// f[i] = min{f[j] - a[i] * (-b[j])}
	// f[i] -> b, f[j] -> y, a[i] -> k, -b[j] -> x
	// k↑, x↑
	f[0] = 0, q.push_back({-b[0], f[0]});
	for(int i = 1; i <= n; i++) {
		while(q.size() >= 2 && q[0].y - a[i] * q[0].x > q[1].y - a[i] * q[1].x) q.pop_front();
		f[i] = q[0].y - a[i] * q[0].x;
		while(q.size() >= 2) {
			auto p0 = q.end()[-2], p1 = q.back(), p2 = (Point){-b[i], f[i]};
			if(((p0.y - p1.y) * (p0.x - p2.x) >= (p0.y - p2.y) * (p0.x - p1.x)) == ((p0.y - p1.y) * (p0.x - p2.x) >= 0 || (p0.y - p2.y) * (p0.x - p1.x) >= 0))
				q.pop_back();
			else break;
		}
		q.push_back({-b[i], f[i]});
	}
	// for(int i = 1; i <= n; i++) printf("%d -> %lld\n", i, f[i]);
	printf("%lld\n", f[n]);
	return 0;
}