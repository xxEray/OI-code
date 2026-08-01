#include <bits/stdc++.h>

typedef long long LL;

LL qpow2(LL y) { LL x = 2, ret = 1; while(true) { if(y & 1) ret = ret * x % 10; if(!(y >>= 1)) return ret; x = x * x % 10; } }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		LL A, B, C;
		scanf("%lld%lld%lld", &A, &B, &C);
		if(A < B) { printf("%lld\n", A == B - 1 && C == B - 1 ? 0LL : qpow2(A)); continue; }
		A = (A - C) % (B - C) + C;
		if(A + 1 == B && C == B - 1) puts("0");
		else printf("%lld\n", qpow2(A));
	}
	return 0;
}