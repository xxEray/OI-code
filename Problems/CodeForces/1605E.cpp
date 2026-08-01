#include <cstdio>
#include <algorithm>
#include <vector>
using std::abs;

typedef long long LL;

const int N = 2e5 + 5;

int n, Q;

struct Equation {
	LL k, b;
	Equation() : k(0), b(0) {}
	Equation(LL k_, LL b_) : k(k_), b(b_) {}
	Equation(LL x) : k(0), b(x) {}
	LL with(LL x) { return k * x + b; }
};
Equation operator+(Equation x, Equation y) { return Equation(x.k + y.k, x.b + y.b); }
Equation operator-(Equation x, Equation y) { return Equation(x.k - y.k, x.b - y.b); }
bool operator<(Equation x, Equation y) { return (-x.b * y.k < -y.b * x.k) ^ (x.k * y.k < 0); } // 按零点排序, -b1/k1 < -b2/k2

Equation ret[N], a[N], b[N], presum[2][N], sufsum[2][N];
std::vector<Equation> add[3];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i].b);
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i].b);
	b[1] = Equation(1, 0);
	scanf("%d", &Q);
	for(int i = 1; i <= n; i++) ret[i] = a[i];
	LL sum = 0;
	for(int i = 1; i <= n; i++) {
		Equation t = b[i] - ret[i];
		for(int j = i; j <= n; j += i) ret[j] = ret[j] + t;
		if(t.k < 0) add[0].push_back(t);
		else if(t.k > 0) add[1].push_back(t);
		else sum += abs(t.b);
	}
	std::sort(add[0].begin(), add[0].end()), std::sort(add[1].begin(), add[1].end());
	int sz0 = add[0].size(), sz1 = add[1].size();
	for(int i = 0; i < sz0; i++) presum[0][i] = (i == 0 ? 0 : presum[0][i - 1]) + add[0][i];
	for(int i = 0; i < sz1; i++) presum[1][i] = (i == 0 ? 0 : presum[1][i - 1]) + add[1][i];
	for(int i = sz0 - 1; i >= 0; i--) sufsum[0][i] = (i == sz0 - 1 ? 0 : sufsum[0][i + 1]) + add[0][i];
	for(int i = sz1 - 1; i >= 0; i--) sufsum[1][i] = (i == sz1 - 1 ? 0 : sufsum[1][i + 1]) + add[1][i];
	// printf("add0: "); for(int i = 0; i < sz0; i++) printf("%dx%+d ", add[0][i].k, add[0][i].b); puts("");
	// printf("pre0: "); for(int i = 0; i < sz0; i++) printf("%dx%+d ", presum[0][i].k, presum[0][i].b); puts("");
	// printf("suf0: "); for(int i = 0; i < sz0; i++) printf("%dx%+d ", sufsum[0][i].k, sufsum[0][i].b); puts("");
	// printf("add1: "); for(int i = 0; i < sz1; i++) printf("%dx%+d ", add[1][i].k, add[1][i].b); puts("");
	// printf("pre1: "); for(int i = 0; i < sz1; i++) printf("%dx%+d ", presum[1][i].k, presum[1][i].b); puts("");
	// printf("suf1: "); for(int i = 0; i < sz1; i++) printf("%dx%+d ", sufsum[1][i].k, sufsum[1][i].b); puts("");
	while(Q--) {
		LL x;
		scanf("%lld", &x);
		int l = 0, r = sz0 - 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(add[0][mid].with(x) < 0) l = mid + 1;
			else r = mid;
		}
		int j0 = l;
		l = 0, r = sz1 - 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(add[1][mid].with(x) > 0) l = mid + 1;
			else r = mid;
		}
		int j1 = l;
		LL ans = 0;
		if(j0 > 0) ans += abs(presum[0][j0 - 1].with(x));
		if(j1 > 0) ans += abs(presum[1][j1 - 1].with(x));
		ans += abs(sufsum[0][j0].with(x)) + abs(sufsum[1][j1].with(x)) + sum;
		printf("%lld\n", ans);
	}
	return 0;
}