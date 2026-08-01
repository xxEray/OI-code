#include <bits/stdc++.h>

typedef long long LL;

LL n, S, K;

bool can;
LL div_ceil(LL x, LL y) { return x < 0 ? x / y : (x + y - 1) / y; }
LL div_floor(LL x, LL y) { return x < 0 ? (x - y + 1) / y : x / y; }

LL calc1(LL l, LL r, LL q) {
	if(l > r) return -1;
	LL x = std::min(div_floor(K - (q - 1) * n - S, q + 1), r);
	// printf("calc1(%lld, %lld, %lld) = (%lld) %lld\n", l, r, q, x, l <= x && (K % (n + x) || can) && q * x >= K - q * n - S ? x : -1);
	return l <= x && (K % (n + x) || can) && (q + 1) * x >= K - q * n ? x : -1;
}
LL calc2(LL l, LL r, LL q) {
	if(l > r) return -1;
	LL x = std::min(div_floor(K - (q - 1) * n - S, q + 1), r);
	// printf("calc2(%lld, %lld, %lld) = (%lld) %lld\n", l, r, q, x, l <= x && (K % (n + x) || can) && (q + 1) * x >= K - q * n ? x : -1);
	return l <= x && (K % (n + x) || can) && q * x >= K - q * n - S ? x : -1;
}
LL solve() {
	K -= S;
	LL ret = -1;
	for(LL i = 1; i <= K && K / i; ) {
		LL j = K / (K / i), q = K / i;
		// printf("i = %lld, j = %lld, q = %lld\n", i, j, q);
		if(j >= n && i <= n + S) ret = std::max(ret, calc1(std::max(i, n) - n, std::min(j, n + S) - n, q));
		if(j >= n + S + 1 && i <= 2 * n) ret = std::max(ret, calc2(std::max(i, n + S + 1) - n, std::min(j, 2 * n) - n, q));
		i = j + 1;
	}
	K += S;
	return ret;
}

int main() {
	LL l, r;
	scanf("%lld%lld%lld%lld", &n, &l, &r, &K);
	S = r - l + 1;
	if(S <= 0) S += n;
	// printf("S = %lld\n", S);
	LL ans = -1;
	can = true; ans = std::max(ans, solve());
	// printf("ans = %lld\n", ans);
	K++;
	can = false; ans = std::max(ans, solve());
	K--;
	if(S <= K && K <= 2 * S) ans = std::max(ans, std::min(K - S + 1, S) + (n - S));
	printf("%lld\n", ans);
	return 0;
}