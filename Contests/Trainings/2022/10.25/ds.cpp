#include <cstdio>
#include <algorithm>
#include <vector>

const int D = (1 << 23) + 1;
char in[D], *I = in, out[D], *O = out;
char gc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
void pc(char c) { O == out + D ? fwrite(O = out, 1, D, stdout) : 0, *O++ = c; }
void read(int &x) {
	char ch = gc();
	while(ch < '0' || ch > '9') ch = gc();
	for(x = 0; '0' <= ch && ch <= '9'; ch = gc()) x = x * 10 + ch - '0';
}
void write(int x, char c = 0) {
	static char stk[20];
	int top = 0;
	if(!x) stk[top++] = '0';
	while(x) stk[top++] = x % 10 + '0', x /= 10;
	for(top--; top >= 0; top--) pc(stk[top]);
	if(c) pc(c);
}

const int N = 2e6 + 5;
const int MAXV = 2e6;
const int INF = 0x3f3f3f3f;

int n, m;
int a[N];

std::vector<int> vct[N];

struct SegmentTree {
	int t[N << 2];
	int (*calc)(int, int);
	int e;
	void build(int x = 1, int l = 1, int r = MAXV) {
		int mid = (l + r) >> 1;
		t[x] = e;
		if(l == r) return;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int qind, int qv, int x = 1, int l = 1, int r = MAXV) {
		if(l == r) { t[x] = calc(t[x], qv); return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = MAXV) {
		if(ql > qr) return e;
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1, ret = e;
		if(ql <= mid) ret = calc(ret, query(ql, qr, x << 1, l, mid));
		if(qr > mid) ret = calc(ret, query(ql, qr, x << 1 | 1, mid + 1, r));
		return ret;
	}
} segmin, segmax;

int mymin(int x, int y) { return x < y ? x : y; }
int mymax(int x, int y) { return x > y ? x : y; }
void chkmax(int &x, int y) { if(x < y) x = y; }

int ans[N];
int c;
struct Query { int x, y, t, id; } q[N * 3];

int main() {
#ifndef DEBUG
	freopen("ds.in", "r", stdin);
	freopen("ds.out", "w", stdout);
#endif
	segmin.calc = mymin, segmin.e = INF;
	segmax.calc = mymax, segmax.e = -INF;
	read(n), read(m);
	for(int i = 1; i <= n; i++) read(a[i]), vct[a[i]].push_back(i);
	for(int i = 1; i <= MAXV; i++) {
		int sz = vct[i].size();
		for(int j = 1; j < sz; j++) if(vct[i][j] > vct[i][j - 1] + 1) q[++c] = (Query){vct[i][j - 1] + 1, vct[i][j] - 1, 0, 0};
		if(sz && vct[i][0] > 1) q[++c] = (Query){1, vct[i][0] - 1, 0, 0};
		if(sz && vct[i][sz - 1] < n) q[++c] = (Query){vct[i][sz - 1] + 1, n, 0, 0};
	}
	for(int i = 1; i <= m; i++) {
		int l, r; read(l), read(r);
		q[++c] = (Query){l, r, 1, i};
	}
//	for(int i = 1; i <= c; i++) printf("[%d, %d], t=%d, id=%d\n", q[i].x, q[i].y, q[i].t, q[i].id);
	std::sort(q + 1, q + c + 1, [&](Query x, Query y) { return x.x > y.x; });
	segmin.build(), segmax.build();
	for(int i = 1; i <= c;) {
		int oldi = i;
		for(; i <= c && q[i].x == q[oldi].x; i++) if(q[i].t == 1) {
			chkmax(ans[q[i].id], segmax.query(1, q[i].y));
			chkmax(ans[q[i].id], q[i].y - segmin.query(q[i].y, MAXV) + 1);
		}
		i = oldi;
		for(; i <= c && q[i].x == q[oldi].x; i++) if(q[i].t == 0) {
			segmax.modify(q[i].y, q[i].y - q[i].x + 1);
			segmin.modify(q[i].y, q[i].x);
		}
	}
	std::sort(q + 1, q + c + 1, [&](Query x, Query y) { return x.x < y.x; });
	segmax.build();
	for(int i = 1; i <= c;) {
		int oldi = i;
		for(; i <= c && q[i].x == q[oldi].x; i++) if(q[i].t == 0)
			segmax.modify(q[i].y, q[i].y);
		i = oldi;
		for(; i <= c && q[i].x == q[oldi].x; i++) if(q[i].t == 1)
			chkmax(ans[q[i].id], segmax.query(1, q[i].y - 1) - q[i].x + 1);
	}
	for(int i = 1; i <= m; i++) write(ans[i], '\n');
	fwrite(out, 1, O - out, stdout);
	return 0;
}