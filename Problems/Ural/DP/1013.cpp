#include <cstdio>
#include <cstring>

#include "biginteger"

long long n, k;
BigInteger m;

template<int r_, int c_>
struct Matrix {
	static const int r = r_;
	static const int c = c_;
	BigInteger a[r_][c_];
	Matrix() { memset(a, 0, sizeof(a)); }
	template<int q_>
	Matrix<r, q_> operator*(const Matrix<c, q_> &rhs) const {
		Matrix<r_, q_> t;
		for(int i = 0; i < t.r; i++)
			for(int j = 0; j < t.c; j++)
				for(int k = 0; k < c; k++)
					t.a[i][j] = (t.a[i][j] + a[i][k] * rhs.a[k][j] % m) % m;
		return t;
	}
};
template<int r, int c> const int Matrix<r, c>::r;
template<int r, int c> const int Matrix<r, c>::c;

Matrix<1, 2> ret;
template<typename T>
void qpow(T a, long long b) {
	for(; b; b >>= 1) {
		if(b & 1) ret = ret * a;
		a = a * a;
	}
}

int main() {
	std::cin >> n >> k >> m;
	ret.a[0][0] = 0, ret.a[0][1] = k - 1;
	Matrix<2, 2> tms;
	tms.a[0][0] = 0, tms.a[0][1] = k - 1, tms.a[1][0] = 1, tms.a[1][1] = k - 1;
	qpow(tms, n - 1);
	std::cout << (ret.a[0][0] + ret.a[0][1]) % m;
	return 0;
} /*
[x, y] => [y, (k - 1)(x + y)]
[x, y] * [0, k - 1] = [y, (k - 1)(x + y)]
         [1, k - 1]
*/