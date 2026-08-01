#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 998244353;

int n;

struct Matrix { int a[2][2]; };
Matrix operator*(const Matrix &x, const Matrix &y) {
	Matrix z;
	z.a[0][0] = (x.a[0][0] * y.a[0][0] + x.a[0][1] * y.a[1][0]) % MOD;
}

struct LCT {
	int ls[N], rs[N], r[N];
} lct;

int main() {

	return 0;
}