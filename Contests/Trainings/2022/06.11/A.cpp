#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e9 + 5;

int A, B, C, K;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d%d", &A, &B, &C, &K);
		long long mod = A + B + C;
		long long ans = A + B;
		long long times = 2;
		while(true) {
			if(K & 1) ans = ans * times % mod;
			if(!(K >>= 1)) break;
			times = times * times % mod;
		}
		printf("%lld\n", (A + B + C - ans) % (A + B + C));
	}
	return 0;
} /*
if 2A > N then A = 2A - N
if 2A < N then A = 2A
1
3 1 8 3
0: 4 8
1: 8 4
2: 4 8
3: 8 4
*/