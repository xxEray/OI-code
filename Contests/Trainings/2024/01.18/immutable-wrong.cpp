#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;
const int V = 5e5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
int a[N];

struct Rectangle {
	int l, r, h;
	LL area;
} rec1[N], rec2a[N], rec2b[N], rec3b[N], rec3c[N];

int lb[N], rb[N];

void get_rec1() {
	std::vector<int> stk;
	for(int i = 1; i <= n; i++) {
		while(!stk.empty() && a[stk.back()] >= a[i]) stk.pop_back();
		lb[i] = rec1[i].l = (stk.empty() ? 1 : stk.back() + 1);
		stk.emplace_back(i);
	}
	stk.clear();
	for(int i = n; i >= 1; i--) {
		while(!stk.empty() && a[stk.back()] >= a[i]) stk.pop_back();
		rb[i] = rec1[i].r = (stk.empty() ? n : stk.back() - 1);
		stk.emplace_back(i);
	}
	for(int i = 1; i <= n; i++) rec1[i].h = a[i], rec1[i].area = (LL)rec1[i].h * (rec1[i].r - rec1[i].l + 1);
}

struct Line {
	LL k, b;
	LL at(int x) const { return k * x + b; }
};
struct LiChaoTree {
	Line t[N << 2];
	void build(int x = 1, int l = 1, int r = V) {
		t[x].k = 1, t[x].b = -LLINF;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void insert(int ql, int qr, Line qv, int x = 1, int l = 1, int r = V) {
		if(l == r) {
			if(t[x].at(l) < qv.at(l)) t[x] = qv;
			return;
		}
		int mid = (l + r) >> 1;
		if(t[x].at(mid) < qv.at(mid)) std::swap(t[x], qv);
		if(ql <= mid && qv.at(l) > t[x].at(l)) insert(ql, qr, qv, x << 1, l, mid);
		if(qr > mid && qv.at(r) > t[x].at(r)) insert(ql, qr, qv, x << 1 | 1, mid + 1, r);
	}
	LL query(int qx, int x = 1, int l = 1, int r = V) {
		if(l == r) return t[x].at(qx);
		int mid = (l + r) >> 1;
		if(qx <= mid) return std::max(query(qx, x << 1, l, mid), t[x].at(qx));
		else return std::max(query(qx, x << 1 | 1, mid + 1, r), t[x].at(qx));
	}
} seg;

void get_upgrade_a(Rectangle *ret, Rectangle *frm) {
	seg.build();
	for(int i = 1; i <= n; i++) seg.insert(frm[i].l, frm[i].r, {-(LL)frm[i].h, frm[i].area});
	for(int i = 1; i <= n; i++) ret[i].l = lb[i], ret[i].r = rb[i], ret[i].h = a[i], ret[i].area = seg.query(lb[i]) + (LL)a[i] * (rb[i] - lb[i] + 1);
	// std::sort(frm + 1, frm + n + 1, [&](const Rectangle &x, const Rectangle &y) { return x.h == y.h ? x.area > y.area : x.h > y.h; });
	// int c = 0;
	// for(int i = 1; i <= n; i++) {
	// 	if(i > 1 && frm[i].h == frm[i - 1].h) continue;
	// 	while(c >= 2 && (frm[c - 1].area - frm[c].area) * (-frm[i].h + frm[c].h) >= (frm[c].area - frm[i].area) * (-frm[c].h + frm[c - 1].h)) c--;
	// 	frm[++c] = frm[i];
	// }
	// for(int i = 1; i <= n; i++) ret[i].l = lb[i], ret[i].r = rb[i], ret[i].h = a[i];
	// std::sort(ret + 1, ret + n + 1, [&](const Rectangle &x, const Rectangle &y) { return x.r - x.l < y.r - y.l; });
	// for(int i = 1, j = 1; i <= n; i++) {
	// 	while(j < c && frm[j + 1].area - (LL)frm[j + 1].h * (ret[i].r - ret[i].l + 1) >= frm[j].area - (LL)frm[j].h * (ret[i].r - ret[i].l + 1)) j++;
	// 	ret[i].area = (LL)ret[i].h * (ret[i].r - ret[i].l + 1) + frm[j].area - (LL)frm[j].h * (ret[i].r - ret[i].l + 1);
	// 	ret[i].l = frm[j].l, ret[i].r = frm[j].r;
	// }
}

void get_upgrade_b(Rectangle *ret, Rectangle *frm) {

}

std::vector<std::pair<LL, int>> vct1[N], vct2[N], vct3[N];
LL f[4][N];
void chkmax(LL &x, LL y) { if(x < y) x = y; }
void dp_answer() {
	for(int i = 0; i <= n; i++) f[0][i] = f[1][i] = f[2][i] = f[3][i] = -LLINF;
	f[0][0] = 0;
	for(int i = 1; i <= n; i++) vct1[rec1[i].r].emplace_back(rec1[i].l - 1, rec1[i].area);
	for(int i = 1; i <= n; i++) vct2[rec2b[i].r].emplace_back(rec2b[i].l - 1, rec2b[i].area);
	for(int i = 1; i <= n; i++) vct3[rec3b[i].r].emplace_back(rec3b[i].l - 1, rec3b[i].area);
	for(int i = 1; i <= n; i++) vct3[rec3c[i].r].emplace_back(rec3c[i].l - 1, rec3c[i].area);
	for(int i = 1; i <= n; i++) {
		f[0][i] = f[0][i - 1], f[1][i] = f[1][i - 1], f[2][i] = f[2][i - 1], f[3][i] = f[3][i - 1];
		for(auto [j, v] : vct1[i]) chkmax(f[1][i], f[0][j] + v), chkmax(f[2][i], f[1][j] + v), chkmax(f[3][i], f[2][j] + v);
		for(auto [j, v] : vct2[i]) chkmax(f[2][i], f[0][j] + v), chkmax(f[3][i], f[1][j] + v);
		for(auto [j, v] : vct3[i]) chkmax(f[3][i], f[0][j] + v);
	}
	chkmax(f[1][n], f[0][n]), chkmax(f[2][n], f[1][n]), chkmax(f[3][n], f[2][n]);
}

int main() {
#ifndef DEBUG
	freopen("immutable.in", "r", stdin);
	freopen("immutable.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	get_rec1();
	get_upgrade_a(rec2a, rec1), get_upgrade_b(rec2b, rec1), get_upgrade_b(rec3b, rec2a);
	printf("rec1:\n"); for(int i = 1; i <= n; i++) printf(" ([l=%d, r=%d], h=%d, area=%lld)\n", rec1[i].l, rec1[i].r, rec1[i].h, rec1[i].area); puts("");
	printf("rec2a:\n"); for(int i = 1; i <= n; i++) printf(" ([l=%d, r=%d], h=%d, area=%lld)\n", rec2a[i].l, rec2a[i].r, rec2a[i].h, rec2a[i].area); puts("");
	printf("rec2b:\n"); for(int i = 1; i <= n; i++) printf(" ([l=%d, r=%d], h=%d, area=%lld)\n", rec2b[i].l, rec2b[i].r, rec2b[i].h, rec2b[i].area); puts("");
	printf("rec3b:\n"); for(int i = 1; i <= n; i++) printf(" ([l=%d, r=%d], h=%d, area=%lld)\n", rec3b[i].l, rec3b[i].r, rec3b[i].h, rec3b[i].area); puts("");
	printf("rec3c:\n"); for(int i = 1; i <= n; i++) printf(" ([l=%d, r=%d], h=%d, area=%lld)\n", rec3c[i].l, rec3c[i].r, rec3c[i].h, rec3c[i].area); puts("");
	dp_answer();
	printf("%lld %lld %lld\n", f[1][n], f[2][n], f[3][n]);
	return 0;
} /*
5
1 3 4 3 1
*/