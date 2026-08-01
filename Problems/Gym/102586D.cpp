#include <cstdio>
#include <algorithm>
#include <cassert>

typedef long long LL;

const int N = 100 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

LL n, A, B;
int a[N];
LL f[N][N];

void chkmin(LL &x, LL y) { if(x > y) x = y; }
bool check(LL x) {
	for(int i = 0; i <= 60; i++) for(int j = 0; j <= 100; j++) f[i][j] = LLINF;
	f[60][0] = 0;
	for(int i = 60; i >= 1; i--) for(int j = 0; j <= 100; j++) {
		if(f[i][j] >= LLINF) continue;
		LL now = f[i][j] * 4 + a[i - 1];
		if(!(x >> (i - 1) & 1)) {
			if(!j && a[i - 1] % 2) continue;
			LL t = std::max(now - (j - (j % 2 != a[i - 1] % 2)), 0LL);
			assert(t % 2 == 0);
			chkmin(f[i - 1][j], t / 2);
		} else {
			for(int k = j; k <= n && (k < 5 || k - j <= 1); k++) {
				LL j_ = n - (k - j);
				if(!j_ && a[i - 1] % 2) continue;
				LL t = std::max(now - (j_ - (j_ % 2 != a[i - 1] % 2)), 0LL);
				assert(t % 2 == 0);
				chkmin(f[i - 1][k], t / 2);
			}
		}
	}
	// printf("check %lld:\n", x);
	// for(int i = 0; i <= 60; i++) for(int j = 0; j <= 100; j++) if(f[i][j] < LLINF) printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
	for(int i = 0; i <= 100; i++) if(f[0][i] == 0) return true;
	return false;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld%lld", &n, &A, &B);
		if(A < B || (A - B) % 2) { puts("-1"); continue; }
		for(int i = 0; i <= 60; i++) a[i] = (B >> i & 1) + ((A - B) / 2 >> i & 1) * 2;
		LL l = 0, r = (1LL << 60);
		while(l < r) {
			LL mid = (l + r) >> 1;
			if(check(mid)) r = mid;
			else l = mid + 1;
		}
		if(!check(l)) puts("-1");
		else printf("%lld\n", l);
	}
	return 0;
} /*
6
3 9 3
4 8 0
6 19 1
1 15 15
2 6 5
5 4 3

1
3 9 3
*/