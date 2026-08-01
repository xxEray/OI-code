#include <bits/stdc++.h>

typedef long long LL;

const LL MOD = 998244353;
const LL inv2 = (MOD + 1) / 2;

LL A, B;

int main() {
	scanf("%lld%lld", &A, &B);
	LL ans = 1;
	bool even = false;
	auto calc = [&](LL i) -> void {
		LL x = 0;
		while(A % i == 0) A /= i, x++;
		even |= (x & 1) && (B & 1);
		// printf("x = %lld\n", x);
		(ans *= (B % MOD * x + 1) % MOD) %= MOD;
	};
	for(LL i = 2; i * i <= A; i++) if(A % i == 0) calc(i);
	if(A != 1) calc(A);
	even |= (~B & 1);
	printf("%lld\n", even ? B % MOD * ans % MOD * inv2 % MOD : (B % MOD * ans - 1 + MOD) % MOD * inv2 % MOD);
	return 0;
}