#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 1e9 + 7;

int n, m;
int a[N];

struct Matrix { LL a[3][3]; };
Matrix operator*(Matrix x, Matrix y) {
	Matrix z;
	memset(z.a, 0, sizeof(z.a));
	for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) for(int k = 0; k < 3; k++) (z.a[i][k] += x.a[i][j] * y.a[j][k]) %= MOD;
	return z;
}

const Matrix trans1 = {{
	{1, 2, 1},
	{0, 1, 1},
	{1, 2, 2}
}};
const Matrix trans2 = {{
	{1, 2, 1},
	{0, 1, 1},
	{0, 0, 1}
}};

int main() {
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	Matrix ans = {{
		{1, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	}};
	a[0] = -1;
	for(int i = 1; i <= n; i++) {
		int v = a[i] - a[i - 1] - 1;
		Matrix tmp = trans1;
		for(; v; v >>= 1, tmp = tmp * tmp) if(v & 1) ans = ans * tmp;
		ans = ans * trans2;
	}
	int v = m - a[n] - 1;
	Matrix tmp = trans1;
	for(; v; v >>= 1, tmp = tmp * tmp) if(v & 1) ans = ans * tmp;
	printf("%lld\n", ans.a[0][2]);
	return 0;
} /*
f[i][
*/