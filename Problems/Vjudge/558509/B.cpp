#include <bits/stdc++.h>

// #define int long long

typedef long long LL;

const int N = 2e4 + 5;
const int M = 100 + 5;
const LL LLINF = 1e12;

int n, m;
LL a[N];

LL f[N][M], g[N][M];
int version[N], version2[N];

struct SegNode { LL k, b; int ls, rs; } t[N * 200];
int cnt;
int nw() { cnt++; assert(cnt < N * 200); t[cnt].ls = t[cnt].rs = 0; t[cnt].k = 0, t[cnt].b = LLINF; return cnt; }
int copy(int x) { cnt++; assert(cnt < N * 200); t[cnt] = t[x]; return cnt; }
int insert(int x, LL qk, LL qb, int l = 1, int r = 20000) {
	// if(l == 1 && r == 20000) printf("insert [%d] y=%dx%+d => %d\n", x, qk, qb, cnt + 1);
	x = copy(x);
	if(l == r) {
		if(t[x].k * l + t[x].b > qk * l + qb) t[x].k = qk, t[x].b = qb;
		return x;
	}
	int mid = (l + r) >> 1;
	if(qk * mid + qb < t[x].k * mid + t[x].b) std::swap(qk, t[x].k), std::swap(qb, t[x].b);
	if(qk * l + qb < t[x].k * l + t[x].b) t[x].ls = insert(t[x].ls, qk, qb, l, mid);
	if(qk * r + qb < t[x].k * r + t[x].b) t[x].rs = insert(t[x].rs, qk, qb, mid + 1, r);
	return x;
}
LL query(int x, LL qx, int l = 1, int r = 20000) {
	// if(l == 1 && r == 20000) printf("query [%d] x=%d ; return %d\n", x, qx, t[x].k * qx + t[x].b);
	if(!x) return LLINF;
	LL ret = t[x].k * qx + t[x].b;
	if(l == r) return ret;
	int mid = (l + r) >> 1;
	if(qx <= mid) return std::min(ret, query(t[x].ls, qx, l, mid));
	else return std::min(ret, query(t[x].rs, qx, mid + 1, r));
}
int merge_down(int x, LL qk, LL qb, int l, int r) {
	x = copy(x);
	if(l == r) {
		if(t[x].k * l + t[x].b > qk * l + qb) t[x].k = qk, t[x].b = qb;
		return x;
	}
	int mid = (l + r) >> 1;
	if(qk * mid + qb < t[x].k * mid + t[x].b) std::swap(qk, t[x].k), std::swap(qb, t[x].b);
	if(qk * l + qb < t[x].k * l + t[x].b) t[x].ls = merge_down(t[x].ls, qk, qb, l, mid);
	if(qk * r + qb < t[x].k * r + t[x].b) t[x].rs = merge_down(t[x].rs, qk, qb, mid + 1, r);
	return x;
}
int merge(int x, int y, int l = 1, int r = 20000) {
	// if(l == 1 && r == 20000) printf("merge [%d] [%d] => ", x, y);
	if(!x || !y) { return x ^ y; }
	int mid = (l + r) >> 1;
	int z = nw();
	t[z].ls = merge(t[x].ls, t[y].ls, l, mid), t[z].rs = merge(t[x].rs, t[y].rs, mid + 1, r);
	t[z].k = t[y].k, t[z].b = t[y].b;
	z = merge_down(z, t[x].k, t[x].b, l, r);
	// if(l == 1 && r == 20000) printf("%d\n", z);
	return z;
}

signed main() {
	t[0].k = 0, t[0].b = LLINF;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 0; i <= n; i++) for(int j = 0; j <= m; j++) f[i][j] = g[i][j] = LLINF;
	g[0][0] = 0;
	for(int k = 1; k <= m; k++) {
		cnt = 0;
		for(int i = 0; i <= n; i++) version[i] = version2[i] = 0;
		version[0] = nw();
		std::vector<int> q;
		for(int i = 1; i <= n; i++) {
			version2[i] = nw();
			while(!q.empty() && a[q.back()] <= a[i]) {
				int j = q.back();
				version2[i] = merge(version2[i], version2[j]);
				q.pop_back();
			}
			version2[i] = insert(version2[i], -(i - 1), g[i - 1][k - 1]);
			f[i][k] = query(version2[i], a[i]) + i * a[i];
			// printf("f[%d][%d] = %d\n", i, k, f[i][k]);
			version[i] = insert(version[q.empty() ? 0 : q.back()], a[i], f[i][k] - i * a[i]);
			q.push_back(i);
			g[i][k] = query(version[i], i);
			// printf("g[%d][%d] = %d\n", i, k, g[i][k]);
		}
	}
	printf("%lld\n", g[n][m]);
	return 0;
}