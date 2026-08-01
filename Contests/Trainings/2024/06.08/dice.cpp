#include <bits/stdc++.h>

typedef long double DB;

const int N = 1e5 + 5;
const DB eps = 1e-11;

int n, m;
int a[N], b[N];

int tmp[4 * N];
void discrete() {
	int c = 0;
	tmp[++c] = 1;
	for(int i = 1; i <= n; i++) tmp[++c] = a[i], tmp[++c] = a[i] + 1;
	for(int i = 1; i <= m; i++) tmp[++c] = b[i], tmp[++c] = b[i] + 1;
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i] = std::lower_bound(tmp + 1, tmp + c + 1, a[i]) - tmp;
	for(int i = 1; i <= m; i++) b[i] = std::lower_bound(tmp + 1, tmp + c + 1, b[i]) - tmp;
}

struct BIT {
	int t[4 * N];
	void clear() { for(int i = 1; i <= 2 * (n + m); i++) t[i] = 0; }
	void add(int x, int v) { while(x <= 2 * (n + m)) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	int query(int l, int r) { return l > r ? 0 : query(r) - query(l - 1); }
} bit;

std::vector<int> vct;
DB c[4 * N], val[4 * N];

bool check1(DB d) {
	DB posi = 1e18, zero = 1e18, nega = 1e18;
	for(int i = 0; i < (int)vct.size(); i++) {
		DB v = val[i] - d * m;
		if(fabs(c[i]) <= eps) zero = std::min(zero, v);
		else if(c[i] < 0) nega = std::min(nega, v / -c[i]);
		else posi = std::min(posi, v / c[i]);
	}
	if(zero < -eps || posi + nega <= eps) return true;
	else return false;
}

bool check2(DB d) {
	DB posi = -1e18, zero = -1e18, nega = -1e18;
	for(int i = 0; i < (int)vct.size(); i++) {
		DB v = val[i] - d * n;
		if(fabs(c[i]) <= eps) zero = std::max(zero, v);
		else if(c[i] < 0) nega = std::max(nega, v / -c[i]);
		else posi = std::max(posi, v / c[i]);
	}
	// printf("check %.3f  zeor=%.3f posi=%.3f nega=%.3f\n", d, zero, posi, nega);
	if(zero > eps || posi + nega >= -eps) return true;
	else return false;
}

int main() {
#ifndef DEBUG
	freopen("dice.in", "r", stdin);
	freopen("dice.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
	std::sort(a + 1, a + n + 1), std::sort(b + 1, b + m + 1);
	discrete();
	DB score = 0;
	for(int i = 1; i <= n; i++) bit.add(a[i], 1);
	for(int i = 1; i <= m; i++) score += bit.query(1, b[i] - 1) + 0.5 * bit.query(b[i], b[i]) - 0.5 * n;
	if(score >= -eps) {
		std::swap(n, m);
		std::swap(a, b);
	}
	vct.emplace_back(1);
	for(int i = 1; i <= n; i++) vct.emplace_back(a[i]), vct.emplace_back(a[i] + 1);
	for(int i = 1; i <= m; i++) vct.emplace_back(b[i]), vct.emplace_back(b[i] + 1);
	std::sort(vct.begin(), vct.end());
	vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
	bit.clear();
	for(int i = 1; i <= m; i++) bit.add(b[i], 1);
	for(int i = 0; i < (int)vct.size(); i++) val[i] = bit.query(1, vct[i] - 1) + 0.5 * bit.query(vct[i], vct[i]);
	bit.clear();
	for(int i = 1; i <= n; i++) bit.add(a[i], 1);
	for(int i = 0; i < (int)vct.size(); i++) c[i] = bit.query(1, vct[i] - 1) + 0.5 * bit.query(vct[i], vct[i]) - 0.5 * n;
	// for(int i = 0; i < (int)vct.size(); i++) printf("%d: c=%.3f, val=%.3f\n", vct[i], c[i], val[i]);
	DB l = 0, r = 1;
	int cnt = 0;
	while(l < r && ++cnt <= 200) {
		DB mid = (l + r) / 2;
		if(check1(mid)) r = mid;
		else l = mid;
	}
	printf("%.9f ", (double)l);
	vct.clear();
	vct.emplace_back(1);
	for(int i = 1; i <= n; i++) vct.emplace_back(a[i]), vct.emplace_back(a[i] + 1);
	for(int i = 1; i <= m; i++) vct.emplace_back(b[i]), vct.emplace_back(b[i] + 1);
	std::sort(vct.begin(), vct.end());
	vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
	bit.clear();
	for(int i = 1; i <= n; i++) bit.add(a[i], 1);
	for(int i = 0; i < (int)vct.size(); i++) val[i] = bit.query(1, vct[i] - 1) + 0.5 * bit.query(vct[i], vct[i]);
	bit.clear();
	for(int i = 1; i <= m; i++) bit.add(b[i], 1);
	for(int i = 0; i < (int)vct.size(); i++) c[i] = bit.query(vct[i] + 1, 2 * (n + m)) + 0.5 * bit.query(vct[i], vct[i]) - 0.5 * m;
	// for(int i = 0; i < (int)vct.size(); i++) printf("%d: c=%.3f, val=%.3f\n", vct[i], c[i], val[i]);
	l = 0, r = 1, cnt = 0;
	while(l < r && ++cnt <= 200) {
		DB mid = (l + r) / 2;
		if(check2(mid)) l = mid;
		else r = mid;
	}
	printf("%.9f\n", (double)l);
	return 0;
} /*
2 1 2
1 1
*/	