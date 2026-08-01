#include <bits/stdc++.h>

#ifndef DEBUG
	#undef assert
	#define assert(...) ((void)0)
#endif

typedef long long LL;

const int N = 5e5 + 5;
const int V = 5e5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
int a[N];

struct SparseTable {
	int go[21][N];
	int calc(int i, int j) { return a[i] <= a[j] ? i : j; }
	void init() {
		for(int i = 1; i <= n; i++) go[0][i] = i;
		for(int j = 1; j <= 20; j++)
			for(int i = 1; i + (1 << j) - 1 <= n; i++)
				go[j][i] = calc(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
	}
	int get(int l, int r) {
		int k = 31 ^ __builtin_clz(r - l + 1);
		return calc(go[k][l], go[k][r - (1 << k) + 1]);
	}
} ST;

struct Line {
	LL k, b;
	LL at(LL x) const { return k * x + b; }
};
struct LiChaoNode {
	Line v;
	int ls, rs;
} t[N * 70];
int nw() { static int cnt = 0; cnt++; t[cnt].v.k = 1, t[cnt].v.b = -LLINF; return cnt; }
void insert(int &x, Line v, int l = 0, int r = V) {
	if(!x) x = nw();
	if(l == r) {
		if(t[x].v.at(l) < v.at(l)) t[x].v = v;
		return;
	}
	int mid = (l + r) >> 1;
	if(t[x].v.at(mid) < v.at(mid)) std::swap(t[x].v, v);
	if(v.at(l) > t[x].v.at(l)) insert(t[x].ls, v, l, mid);
	if(v.at(r) > t[x].v.at(r)) insert(t[x].rs, v, mid + 1, r);
}
LL query(int x, int qx, int l = 0, int r = V) {
	if(!x) return -LLINF;
	if(l == r) return t[x].v.at(qx);
	int mid = (l + r) >> 1;
	if(qx <= mid) return std::max(query(t[x].ls, qx, l, mid), t[x].v.at(qx));
	else return std::max(query(t[x].rs, qx, mid + 1, r), t[x].v.at(qx));
}
void merge(int &x, int y, int l = 0, int r = V) {
	if(!x || !y) { x ^= y; return; }
	if(l == r) {
		if(t[x].v.at(l) < t[y].v.at(l)) t[x].v = t[y].v;
		return;
	}
	int mid = (l + r) >> 1;
	merge(t[x].ls, t[y].ls, l, mid);
	merge(t[x].rs, t[y].rs, mid + 1, r);
	if(t[x].v.at(mid) < t[y].v.at(mid)) std::swap(t[x].v, t[y].v);
	if(t[y].v.at(l) > t[x].v.at(l)) insert(t[x].ls, t[y].v, l, mid);
	if(t[y].v.at(r) > t[x].v.at(r)) insert(t[x].rs, t[y].v, mid + 1, r);
}

void chkmax(LL &x, LL y) { if(x < y) x = y; }

LL ans1, ans2, ans3;
int f[4][N];
int cid;
void solve(int id, int l, int r) {
	printf("solve (%d, %d) id=%d\n", l, r, id);
	assert(l <= r);
	if(l == r) {
		f[1][id] = nw(), f[2][id] = nw(), f[3][id] = nw();
		insert(f[1][id], {-1LL, (LL)a[l]});
		return;
	}
	LL v = a[ST.get(l, r)];
	// printf("[%d, %d]: v = %lld\n", l, r, v);
	std::vector<std::pair<int, int>> vct;
	for(int last = l; last <= r;) {
		int nxt = ST.get(last, r);
		if(a[nxt] != v) {
			vct.emplace_back(last, r);
			break;
		}
		if(last <= nxt - 1) vct.emplace_back(last, nxt - 1);
		last = nxt + 1;
	}
	f[1][id] = nw(), f[2][id] = nw(), f[3][id] = nw();
	LL val = (LL)(r - l + 1) * v;
	LL g[3] = {0, -LLINF, -LLINF};
	LL tmp[4] = {0, -LLINF, -LLINF, -LLINF};
	for(auto [p, q] : vct) {
		int nid = ++cid;
		solve(nid, p, q);
		LL h[3] = {g[0], g[1], g[2]};
		LL res = query(f[1][nid], v);
		chkmax(h[1], g[0] + res), chkmax(h[2], g[1] + res);
		res = query(f[2][nid], v);
		if(l == 1 && r == 5) printf("! [%d, %d] %lld\n", p, q, res);
		chkmax(h[2], g[0] + res);
		g[0] = h[0], g[1] = h[1], g[2] = h[2], g[3] = h[3];
		LL tmp2[4] = {tmp[0], tmp[1], tmp[2], tmp[3]};
		res = query(f[1][nid], 0);
		chkmax(tmp2[1], tmp[0] + res), chkmax(tmp2[2], tmp[1] + res), chkmax(tmp2[3], tmp[2] + res);
		res = query(f[2][nid], 0);
		chkmax(tmp2[2], tmp[0] + res), chkmax(tmp2[3], tmp[1] + res);
		res = query(f[3][nid], 0);
		chkmax(tmp2[3], tmp[0] + res);
		tmp[0] = tmp2[0], tmp[1] = tmp2[1], tmp[2] = tmp2[2], tmp[3] = tmp2[3];
		merge(f[1][id], f[1][nid]), merge(f[2][id], f[2][nid]), merge(f[3][id], f[3][nid]);
	}
	chkmax(ans1, tmp[1]), chkmax(ans2, tmp[2]), chkmax(ans3, tmp[3]);
	printf("[%d, %d]: g = %lld %lld %lld\n", l, r, g[0] + val, g[1] + val, g[2] + val);
	insert(f[1][id], {-(LL)(r - l + 1), g[0] + val}), insert(f[2][id], {-(LL)(r - l + 1), g[1] + val}), insert(f[3][id], {-(LL)(r - l + 1), g[2] + val});
}

int main() {
#ifndef DEBUG
	freopen("immutable.in", "r", stdin);
	freopen("immutable.out", "w", stdout);
#endif
	// printf("%.5f\n", (sizeof(t) + sizeof(ST) + sizeof(f)) / 1024. / 1024);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	ST.init();
	solve(++cid, 1, n);
	chkmax(ans1, query(f[1][1], 0)), chkmax(ans2, query(f[2][1], 0)), chkmax(ans3, query(f[3][1], 0));
	chkmax(ans1, 0), chkmax(ans2, ans1), chkmax(ans3, ans2);
	printf("%lld %lld %lld\n", ans1, ans2, ans3);
	return 0;
} /*
5
8 7 3 6 2 
*/