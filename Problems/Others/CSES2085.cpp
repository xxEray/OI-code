#include <cstdio>
#include <algorithm>
#include <deque>
#include <assert.h>

typedef long long LL;

const int N = 4e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

LL a[N], b[N];
int n;

LL f[N];

struct Point {
	LL x, y;
	Point() = default;
	Point(LL x_, LL y_) : x(x_), y(y_) {}
};
std::deque<Point> q;

int order[N];
void cdq(int l, int r) {
	if(l >= r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid);
	q.clear();
	for(int i = l; i <= mid; i++) order[i] = i;
	std::sort(order + l, order + mid + 1, [](int x, int y) { return b[x] == b[y] ? f[x] > f[y] : -b[x] < -b[y]; });
	for(int j = l; j <= mid; j++) {
		int i = order[j];
		while(q.size() >= 2) {
			auto p0 = q.end()[-2], p1 = q.back(), p2 = (Point){-b[i], f[i]};
			if(((p0.y - p1.y) * (p0.x - p2.x) >= (p0.y - p2.y) * (p0.x - p1.x)) == ((p0.y - p1.y) * (p0.x - p2.x) >= 0 || (p0.y - p2.y) * (p0.x - p1.x) >= 0))
				q.pop_back();
			else break;
		}
		q.push_back({-b[i], f[i]});
	}
	for(int i = mid + 1; i <= r; i++) order[i] = i;
	std::sort(order + (mid + 1), order + r + 1, [](int x, int y) { return a[x] < a[y]; });
	for(int j = mid + 1; j <= r; j++) {
		int i = order[j];
		while(q.size() >= 2 && q[0].y - a[i] * q[0].x > q[1].y - a[i] * q[1].x) q.pop_front();
		f[i] = std::min(f[i], q[0].y - a[i] * q[0].x);
	}
	cdq(mid + 1, r);
}

int main() {
	// freopen("D:/Useless/Temp/in.txt", "r", stdin);
	scanf("%d%lld", &n, &b[0]);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	for(int i = 1; i <= n; i++) f[i] = LLINF;
	cdq(0, n);
	printf("%lld\n", f[n]);
	return 0;
}