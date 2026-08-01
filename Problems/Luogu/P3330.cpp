#include <cstdio>
#include <algorithm>
#include <biginteger>

int n, m;

BigInteger p, q, g;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		if(m < n) { puts("0 1"); continue; }
		p = pow((BigInteger)(m + 1), n - 1) * (m - n + 1);
		q = pow((BigInteger)m, n);
		g = gcd(m + 1 - n, q);
		p /= g, q /= g;
		p.print(' '), q.print('\n');
	}
	return 0;
}