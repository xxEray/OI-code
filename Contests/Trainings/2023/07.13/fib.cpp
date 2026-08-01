#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 1e9 + 7;

int n;
int a[N];

struct Matrix {
	int a[2][2];
	Matrix() { memset(a, 0, sizeof(a)); }
};
Matrix operator*(Matrix x, Matrix y) {
	Matrix z;
	for(int i = 0; i <= 1; i++) for(int j = 0; j <= 1; j++) for(int k = 0; k <= 1; k++) (z.a[i][j] += x.a[i][k] * y.a[k][j]) %= MOD;
	return z;
}
Matrix trans(int gap) {
	Matrix x;
	x.a[0][0] = x.a[1][0] = 1;
	x.a[0][1] = (gap + 1) / 2, x.a[1][1] = gap / 2;
}
struct FHQ {
	int c[N][2], sz[N], w[N];
	Matrix v[N], t[N];
	int rt, cnt;
	FHQ() { t[0].a[0][0] = t[0].a[1][1] = 1; }
	int nw(int gap) { cnt++; w[cnt] = (rand() << 15 | rand()); c[cnt][0] = c[cnt][1] = 0; v[cnt] = trans(gap); pushup(cnt); return cnt; }
	void pushup(int x) { sz[x] = sz[c[x][0]] + sz[c[x][1]] + 1; t[x] = t[c[x][0]] * v[x] * t[c[x][1]]; }
	int merge(int x, int y) {
		if(!x || !y) return x ^ y;
		if(w[x] > w[y]) c[x][1] = merge(c[x][1], y), pushup(x);
		else c[y][0] = merge(x, c[y][0]), pushup(x);
	}
	void split(int root, int size, int &x, int &y) {
		if(!root) { x = y = 0; return; }
		if(size <= sz[c[root][0]]) y = root, split(c[root][0], size, x, c[y][0]), pushup(root);
		else x = root, split(c[root][1], size - sz[c[root][0]] - 1, c[x][1], y), pushup(root);
	}
	void insert(int )
} treap;

int main() {
#ifndef DEBUG
	freopen("fib.in", "r", stdin);
	freopen("fib.out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	
	return 0;
}