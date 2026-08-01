#include <cstdio>
#include <algorithm>
#include <cmath>

const int N = 100 + 5;
const double eps = 1e-8;

struct Vertice {
	double x, y;
	void set_point(double x_, double y_) { x = x_, y = y_; }
	void set_line(int y_) { x = 205, y = y_; }
	bool line() const { return x > 204; }
};
double distance(const Vertice &lhs, const Vertice &rhs) {
	if(!lhs.line() && !rhs.line())
		#define sq(x) ((x) * (x))
		return std::sqrt(sq(lhs.x - rhs.x) + sq(lhs.y - rhs.y));
		#undef sq
	else if(lhs.line() && rhs.line()) return std::abs(lhs.y - rhs.y);
	else return std::abs(lhs.y - rhs.y);
}

Vertice a[N];
int n;

int fa[N];
void init() { for(int i = 1; i <= n + 2; i++) fa[i] = i; }
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

bool check(double x) {
	init();
	for(int i = 1; i <= n + 2; i++)
		for(int j = 1; j <= n + 2; j++)
			if(i != j && x - distance(a[i], a[j]) > eps) {
				int x = find(i), y = find(j);
				if(x != y) fa[x] = y;
			}
	// std::printf("check %lf\n", x);
	if(find(1) == find(2)) return false;
	else return true;
}

int main() {
	std::scanf("%d", &n);
	a[1].set_line(100);
	a[2].set_line(-100);
	for(int i = 3; i <= n + 2; i++) {
		double x, y;
		std::scanf("%lf%lf", &x, &y);
		a[i].set_point(x, y);
	}
	// for(int i = 1; i <= n + 2; i++)
	// 	for(int j = 1; j <= n + 2; j++) {
	// 		if(i < 3) std::printf("Line[%d]\t<-->\t", (int)a[i].y);
	// 		else std::printf("(%.0lf, %.0lf) \t<-->\t", a[i].x, a[i].y);
	// 		if(j < 3) std::printf("Line[%d]\t= ", (int)a[j].y);
	// 		else std::printf("(%.0lf, %.0lf)  \t= ", a[j].x, a[j].y);
	// 		std::printf("%.3lf\n", distance(a[i], a[j]));
	// 	}
	double l = 0, r = 200;
	while(r - l > eps) {
		double mid = (l + r) / 2;
		if(check(mid * 2)) l = mid;
		else r = mid;
	}
	std::printf("%.5lf", l);
	return 0;
}