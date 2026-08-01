#include <bits/stdc++.h>

const int N = (1 << 6) + 5;

int n, m;
int p, K;
int a[3];

int U;

struct Matrix {
	unsigned a[N][N];
	Matrix() { memset(a, 0, sizeof(a)); }
};
Matrix operator*(const Matrix &x, const Matrix &y) {
	Matrix z;
	for(int i = 0; i <= U; i++) for(int j = 0; j <= U; j++) for(int k = 0; k <= U; k++) z.a[i][j] += x.a[i][k] * y.a[k][j];
	return z;
}

Matrix ret, trans;

bool check(int s, int t) {
	int vs = 0, vt = 0;
	for(int i = 0; i < m; i++) if(s >> i & 1) vs |= a[1] << i >> K, vt |= a[2] << i >> K;
	for(int i = 0; i < m; i++) if(t >> i & 1) vs |= a[0] << i >> K, vt |= a[1] << i >> K;
	// if(!(vs & s) && !(vt & t)) printf("check(%d, %d) = true\n", s, t);
	return !(vs & s) && !(vt & t);
}

bool check(int s) {
	int v = 0;
	for(int i = 0; i < m; i++) if(s >> i & 1) v |= a[1] << i >> K;
	// if(!(v & s)) printf("check(%d) = true\n", s);
	return !(v & s);
}

int main() {
	scanf("%d%d", &n, &m);
	scanf("%d%d", &p, &K);
	for(int i = 0; i <= 2; i++) for(int j = 0; j < p; j++) { int x; scanf("%d", &x); if(i != 1 || j != K) a[i] |= x << j; }
	U = (1 << m) - 1;
	for(int s = 0; s <= U; s++) if(check(s))
		for(int t = 0; t <= U; t++) if(check(s, t))
			trans.a[s][t] = 1;
	for(int s = 0; s <= U; s++) if(check(s)) ret.a[0][s] = 1;
	n--;
	while(true) {
		if(n & 1) ret = ret * trans;
		if(!(n >>= 1)) break;
		trans = trans * trans;
	}
	unsigned ans = 0;
	for(int s = 0; s <= U; s++) if(check(s)) ans += ret.a[0][s];
	printf("%u\n", ans);
	return 0;
}