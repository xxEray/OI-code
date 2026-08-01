#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 80;
const int S = (1 << 20) + 5;

const LL prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

LL L, R;

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }
LL lcm(LL x, LL y) { return x / gcd(x, y) * y; }

int mask[N];
LL f[N][S];

int main() {
	scanf("%lld%lld", &L, &R);
	int U = (1 << 20) - 1;
	for(LL i = L; i <= R; i++) for(int j = 0; j < 20; j++) if(i % prime[j] == 0) mask[i - L + 1] |= 1 << j;
	// for(LL i = L; i <= R; i++) printf("mask %lld %d\n", i, mask[i - L + 1]);
	f[0][0] = 1;
	for(LL i = L; i <= R; i++)
		for(int j = 0; j <= U; j++) {
			f[i - L + 1][j] += f[i - L][j];
			if((mask[i - L + 1] & j) == 0) f[i - L + 1][j | mask[i - L + 1]] += f[i - L][j];
		}
	// for(LL i = L; i <= R; i++)
	// 	for(int j = 0; j <= U; j++)
	// 		if(f[i - L + 1][j]) printf("f %lld %d %lld\n", i, j, f[i - L + 1][j]);
	LL ans = 0;
	for(int s = 0; s <= U; s++) ans += f[R - L + 1][s];
	printf("%lld\n", ans);
	return 0;
}