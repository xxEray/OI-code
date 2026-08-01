#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 100 + 5;
const LL MOD = 1e9 + 7;

int n;
LL m;
LL a[N];

struct Matrix { LL a[N][N]; };

Matrix mul(Matrix &a, Matrix &b) {
	Matrix c;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			c.a[i][j] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			for(int k = 1; k <= n; k++)
				(c.a[i][j] += a.a[i][k] * b.a[k][j] % MOD) %= MOD;
	return c;
}

Matrix g, base;

int count(LL x) {
	int cnt = 0;
	while(x) cnt += (x & 1), x >>= 1;
	return cnt;
}

int main() {
	scanf("%d%lld", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			g.a[i][j] = (count(a[i] ^ a[j]) % 3 == 0);
	for(int i = 1; i <= n; i++) base.a[1][i] = 1;
	for(--m; m; m >>= 1) {
		if(m & 1) base = mul(base, g);
		g = mul(g, g);
	}
	LL ans = 0;
	for(int i = 1; i <= n; i++) (ans += base.a[1][i]) %= MOD;
	printf("%lld\n", ans);
	return 0;
}