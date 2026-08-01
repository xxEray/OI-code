#include <bits/stdc++.h>

typedef long long LL;

const LL MOD = 1e9 + 7;

struct Matrix { LL a[40][40]; };
Matrix operator*(Matrix x, Matrix y) {
	Matrix z;
	for(int i = 0; i <= 31; i++) for(int j = 0; j <= 31; j++) z.a[i][j] = 0;
	for(int i = 0; i <= 31; i++) for(int j = 0; j <= 31; j++) for(int k = 0; k <= 31; k++) (z.a[i][j] += x.a[i][k] * y.a[k][j]) %= MOD;
	return z;
}

Matrix trans, ret;

int main() {
	LL n;
	scanf("%lld", &n);
	if(n == 1) { puts("1"); return 0; }
	else if(n == 2) { puts("2"); return 0; }
	for(int s = 0; s <= 31; s++) if(s & 1)
		for(int i = 0; i < 5; i++)
			if(~(s >> 1) >> i & 1)
				trans.a[s][(s >> 1) | (1 << i)]++;
	for(int i = 0; i < 125; i++) {
		int x = i % 5, y = i / 5 % 5, z = i / 25;
		if(x != y && x != z && y != z && std::abs(x) <= 2 && std::abs(y - 1) <= 2 && std::abs(z - 2) <= 2)
			ret.a[0][(1 << x) | (1 << y) | (1 << z)]++;
	}
	n -= 3;
	while(true) {
		if(n & 1) ret = ret * trans;
		if(!(n >>= 1)) break;
		trans = trans * trans;
	}
	printf("%lld\n", ret.a[0][7]);
	return 0;
}