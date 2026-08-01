#include <cstdio>
#include <algorithm>

typedef long long LL;

#define bit(x, y) ((x) >> (y) & 1)
#define pow2(x) (1LL << (x))
#define length(l, r) ((r) - (l) + 1)

int main() {
	LL L, R;
	scanf("%lld%lld", &L, &R);
	if(L == R) { puts("1"); return 0; }
	int lim, k;
	for(lim = 60; lim >= 0; lim--) if(bit(R, lim) && !bit(L, lim)) break;
	for(k = lim - 1; k >= 0; k--) if(bit(R, k)) break;
	for(int i = 60; i > lim; i--) if(bit(L, i)) L -= pow2(i), R -= pow2(i);
	LL L1 = L, R1 = pow2(lim) - 1;
	LL L2 = L + pow2(lim), R2 = pow2(lim + 1) - 1;
	LL L3 = pow2(lim), R3 = pow2(lim) + pow2(k + 1) - 1;
	if(R3 < L2) std::swap(L2, L3), std::swap(R2, R3);
	// printf("lim = %d, k = %d\n", lim, k);
	// printf("L1 = %lld, R1 = %lld\n", L1, R1);
	// printf("L2 = %lld, R2 = %lld\n", L2, R2);
	// printf("L3 = %lld, R3 = %lld\n", L3, R3);
	if(L3 <= R2) L2 = std::min(L2, L3), R2 = std::max(R2, R3), L3 = 1, R3 = 0;
	if(L2 <= R1) L1 = std::min(L1, L2), R1 = std::max(R1, R2), L2 = 1, R2 = 0;
	printf("%lld\n", length(L1, R1) + length(L2, R2) + length(L3, R3));
	return 0;
}