#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2000 + 5;

LL n, mod;
int K;

struct Matrix { LL a[2][2]; };
Matrix mul(Matrix x, Matrix y) {
	Matrix z;
	z.a[0][0] = z.a[0][1] = z.a[1][0] = z.a[1][1] = 0;
	for(int i = 0; i <= 1; i++) for(int j = 0; j <= 1; j++) for(int k = 0; k <= 1; k++) (z.a[i][j] += x.a[i][k] * y.a[k][j]) %= mod;
	return z;
}
const Matrix unit = {{{1, 0}, {0, 1}}};
Matrix res, trans;
Matrix qpow(Matrix x, LL y) { Matrix ret = unit; while(true) { if(y & 1) ret = mul(ret, x); if(!(y >>= 1)) return ret; x = mul(x, x); } }
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL inv(LL x) { return qpow(x, mod - 2); }

int main() {
	scanf("%lld%d%lld", &n, &K, &mod);
	if(K & 1) {
		trans.a[0][0] = 0, trans.a[0][1] = K - 1, trans.a[1][0] = 1, trans.a[1][1] = K - 2;
		res.a[0][0] = 1, res.a[0][1] = 0, res.a[1][0] = res.a[1][1] = 0;
		res = mul(res, qpow(trans, n));
		LL ans = qpow(K, n);
		(ans += mod - res.a[0][0]) %= mod;
		for(int i = 1; i < K; i++) {
			LL x = ((i & 1) ? (i + K) / 2 : i / 2);
			if(2 * x % K == (i + n * x) % K) (ans += mod - res.a[0][1] * inv(K - 1) % mod) %= mod;
		}
		printf("%lld\n", ans);
	} else {
		
	}
	return 0;
}