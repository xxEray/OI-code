#include <bits/stdc++.h>

typedef long long LL;

const LL MOD = 1e9 + 7;

const int N = 1e6 + 5;

char strn[N], strm[N];

struct Matrix {
	LL a[2][2];
	Matrix() { a[0][0] = a[0][1] = a[1][0] = a[1][1] = 0; }
};
Matrix operator*(const Matrix &x, const Matrix &y) {
	Matrix z;
	for(int i = 0; i <= 1; i++) for(int j = 0; j <= 1; j++) for(int k = 0; k <= 1; k++) (z.a[i][j] += x.a[i][k] * y.a[k][j]) %= MOD;
	return z;
}

void sub(char *str) {
	int n = strlen(str);
	for(int i = n - 1; i >= 0; i--)
		if(str[i] > '0') { str[i]--; break; }
		else str[i] = '9';
}

void multiply(Matrix &base, Matrix x, char *y) {
	int len = strlen(y);
	for(int i = len - 1; i >= 0; i--) {
		for(int j = 1; j <= y[i] - '0'; j++) base = base * x;
		x = x * x * x * x * x * x * x * x * x * x;
	}
}

int main() {
	LL a, b, c, d;
	scanf("%s%s%lld%lld%lld%lld", strn, strm, &a, &b, &c, &d);
	sub(strn), sub(strm);
	Matrix trans1, trans2, ans, tmp;
	trans1.a[0][0] = a, trans1.a[1][0] = b, trans1.a[1][1] = 1;
	trans2.a[0][0] = c, trans2.a[1][0] = d, trans2.a[1][1] = 1;
	ans.a[0][0] = 1, ans.a[0][1] = 1;
	tmp.a[0][0] = tmp.a[1][1] = 1;
	multiply(tmp, trans1, strm), tmp = tmp * trans2;
	multiply(ans, tmp, strn);
	multiply(ans, trans1, strm);
	printf("%lld\n", ans.a[0][0]);
	return 0;
}