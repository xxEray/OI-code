#include <cstdio>
#include <algorithm>
#include <map>
#include <array>
#include <vector>

typedef long long LL;

const int N = 3e5 + 5;

int n, m;
struct Node { int st, ed, x, y; } a[N];
std::map<std::pair<int, int>, int> mp;

int r[N], c[N];
struct DSU {
	int fa[N], sz[N];
	std::vector<std::array<int, 3>> ops;
	void init() { for(int i = 1; i <= n; i++) fa[i] = i, r[i] = c[i] = 1, sz[i] = 1; }
	int find(int x) { return x == fa[x] ? x : find(fa[x]); }
	void merge(int x, int y, int type) {
		// printf("    merge(%d, %d)\n", x, y);
		x = find(x), y = find(y);
		ops.emplace_back();
		auto &p = ops.back();
		if(x == y) { p[0] = -1; return; }
		if(sz[x] > sz[y]) std::swap(x, y);
		p[0] = x, p[1] = y;
		fa[x] = y;
		sz[y] += sz[x];
		p[2] = type;
		if(type) r[y] += r[x] - 1, c[y] += c[x];
		else c[y] += c[x] - 1, r[y] += r[x];
	}
	void undo() {
		// printf("    undo\n");
		auto p = ops.back();
		ops.pop_back();
		if(p[0] == -1) return;
		int x = p[0], y = p[1];
		fa[x] = x;
		sz[y] -= sz[x];
		if(p[2]) r[y] -= r[x] - 1, c[y] -= c[x];
		else c[y] -= c[x] - 1, r[y] -= r[x];
	}
	LL calc(int x) { return (LL)r[find(x)] * c[find(x)]; }
} dsu;

LL ans;
int rid[N], cid[N];
LL out[N];

std::vector<std::array<LL, 5>> ops;
void insert(int i) {
	// printf("insert #%d (%d, %d)\n", i, a[i].x, a[i].y);
	ops.emplace_back();
	auto &p = ops.back();
	if(rid[a[i].x] && cid[a[i].y] && dsu.find(rid[a[i].x]) == dsu.find(cid[a[i].y])) { p[0] = -1; return; }
	p[0] = ans;
	int cnt = 0;
	if(rid[a[i].x]) ans -= dsu.calc(rid[a[i].x]), dsu.merge(rid[a[i].x], i, 0), cnt++;
	if(cid[a[i].y]) ans -= dsu.calc(cid[a[i].y]), dsu.merge(cid[a[i].y], i, 1), cnt++;
	p[1] = cnt;
	ans += dsu.calc(i);
	p[2] = i, p[3] = rid[a[i].x], p[4] = cid[a[i].y];
	rid[a[i].x] = i, cid[a[i].y] = i;
}
void undo() {
	// printf("undo\n");
	auto p = ops.back();
	ops.pop_back();
	if(p[0] == -1) return;
	ans = p[0];
	while(p[1]--) dsu.undo();
	int i = p[2];
	rid[a[i].x] = p[3], cid[a[i].y] = p[4];
}
LL answer() {
	// printf("answer %lld\n", ans);
	return ans;
}

struct CdqByTime {
	std::vector<int> t[N << 2];
	void modify(int ql, int qr, int qv, int x = 1, int l = 1, int r = m) {
		if(ql <= l && r <= qr) { t[x].push_back(qv); return; }
		int mid = (l + r) >> 1;
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
	}
	void solve(int x = 1, int l = 1, int r = m) {
		int cnt = 0;
		for(int i : t[x]) insert(i), cnt++;
		int mid = (l + r) >> 1;
		if(l == r) out[l] = answer();
		else solve(x << 1, l, mid), solve(x << 1 | 1, mid + 1, r);
		while(cnt--) undo();
	}
} cdq;

int main() {
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		if(mp.count({x, y})) {
			int id = mp[{x, y}];
			a[id].ed = i - 1;
			mp.erase({x, y});
		} else {
			int id = ++n;
			a[id].st = i;
			a[id].x = x, a[id].y = y;
			mp[{x, y}] = id;
		}
	}
	for(auto p : mp) a[p.second].ed = m;
	// for(int i = 1; i <= n; i++) printf("(%d, %d) [%d .. %d]\n", a[i].x, a[i].y, a[i].st, a[i].ed);
	dsu.init();
	for(int i = 1; i <= n; i++) cdq.modify(a[i].st, a[i].ed, i);
	cdq.solve();
	for(int i = 1; i <= m; i++) printf("%lld ", out[i]);
	puts("");
	return 0;
}