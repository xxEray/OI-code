#include <cstdio>

typedef long long LL;

int main() {
	int n;
	scanf("%d", &n);
	LL A = 0, B = 0, C = 0;
	scanf("%lld%lld", &A, &B);
	for(int i = 3; i <= n; i++) {
		LL x;
		scanf("%lld", &x);
		C ^= x;
	}
	LL D = (A + B - C) >> 1;
	if(((A + B - C) & 1) || D < 0 || D > A || D & C)
		{ puts("-1"); return 0; }
	LL a = D;
	for(int i = 60; i >= 0; i--)
		if((C & (1LL << i)) && (a | (1LL << i)) <= A)
			a |= (1LL << i);
	printf("%lld\n", a == 0 ? -1LL : A - a);
	return 0;
}