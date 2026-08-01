#include <cstdio>
#include <algorithm>
#include <cmath>

const int N = 20 + 5;
const int M = 250 + 5;
const double eps = 1e-6;

int n, m;

int cna, cnb;
struct Point {
	int x, y;
	Point() {}
	Point(int x_, int y_) : x(x_), y(y_) {}
	int hash() const { return x * (n + 1) + y; }
} a[M], b[M];
int cn;
struct Segment {
	double k, b;
	int xl, xr;
	Segment() {}
	Segment(Point p, Point q) {
		k = (double)(q.y - p.y) / (q.x - p.x);
		b = p.y - k * p.x;
		xl = std::min(p.x, q.x), xr = std::max(p.x, q.x);
	}
} d[M * 8];

bool horse(Point p, Point q) { return (std::abs(p.x - q.x) == 1 && std::abs(p.y - q.y) == 2) || (std::abs(p.x - q.x) == 2 && std::abs(p.y - q.y) == 1); }

bool intersect(Segment p, Segment q) {
	double x = (q.b - p.b) / (p.k - q.k);
	return p.xl + eps <= x && x <= p.xr - eps && q.xl + eps <= x && x <= q.xr - eps;
}

bool check(Segment t) {
	for(int i = 1; i <= cn; i++) if(intersect(t, d[i])) return false;
	return true;
}

int fa[N * N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int main() {
	while(scanf("%d%d", &n, &m) == 2 && (n | m)) {
		cn = cna = cnb = 0;
		for(int i = 0; i <= (n + 1) * (n + 1); i++) fa[i] = i;
		for(int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			if(i & 1) {
				a[++cna] = {x, y};
				for(int j = 1; j < cna; j++) if(horse(a[j], a[cna])) {
					Segment t(a[j], a[cna]);
					if(check(t)) d[++cn] = t, merge(a[j].hash(), a[cna].hash());
				}
			} else {
				b[++cnb] = {x, y};
				for(int j = 1; j < cnb; j++) if(horse(b[j], b[cnb])) {
					Segment t(b[j], b[cnb]);
					if(check(t)) d[++cn] = t, merge(b[j].hash(), b[cnb].hash());
				}
			}
		}
		// for(int i = 1; i <= cn; i++) printf("%.3fx + %.3f [%d, %d]\n", d[i].k, d[i].b, d[i].xl, d[i].xr);
		bool flag = false;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) flag |= find(Point(0, i).hash()) == find(Point(n, j).hash());
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) flag |= find(Point(i, 0).hash()) == find(Point(j, n).hash());
		puts(flag ? "yes" : "no");
	}
	return 0;
}