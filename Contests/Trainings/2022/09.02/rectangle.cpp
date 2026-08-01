#include <cstdio>
#include <algorithm>
#include <cassert>

typedef long long LL;

const int N = 25000 + 5;
const int dir[9][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {0, 0}};

int n, m, Q;

int a[N][4], b[N * 4][3], copy[N][4];
LL out[N];

struct BIT {
	int t[N * 8], mx;
	void modify(int x, int v) { while(x <= mx) t[x] += v, x += x & -x; }
	LL query(int x) { LL ret = 0; while(x) ret += t[x], x -= x & -x; return ret; }
	LL query(int l, int r) { return query(r) - query(l - 1); }
} bit, bit2;

struct Point { int x, y, t, w; } p[N * 9];
void solve(int d1, int d2, bool origin) {
	int c = 0;
	for(int i = 1; i <= n; i++) copy[i][0] = a[i][0], copy[i][1] = a[i][1], copy[i][2] = a[i][2], copy[i][3] = a[i][3];
	for(int i = 1; i <= n + m; i++) {
		if(b[i][1] == d1 || b[i][1] == d2 || (b[i][1] == 8 && origin)) {
			int id = b[i][0], d = b[i][1];
			p[++c] = {a[id][0] + dir[d][0], a[id][1], }
		}
		a[i][0] += b[i][2] * dir[b[i][1]][0], a[i][2] += b[i][2] * dir[b[i][1]][0];
		a[i][1] += b[i][2] * dir[b[i][1]][1], a[i][3] += b[i][2] * dir[b[i][1]][1];
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &Q);
	bit.mx = (n + m) * 4, bit2.mx = (n + m) * 4;
	for(int i = 1; i <= n; i++) scanf("%d%d%d%d", &a[i][0], &a[i][1], &a[i][2], &a[i][3]);
	for(int i = 1; i <= n; i++) b[i][0] = i, b[i][1] = 8, b[i][2] = 0;
	for(int i = 1; i <= m; i++) scanf("%d%d%d", &b[i + n][0], &b[i + n][1], &b[i + n][2]);

	return 0;
}