#include <bits/stdc++.h>
#include <cassert>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
int a[N];

LL f[N][2];

inline void chkmin(LL &x, LL y) { if(x > y) x = y; }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		a[0] = a[n + 1] = 0;
		for(int i = 0; i <= n + 1; i++) f[i][0] = f[i][1] = LLINF;
		f[1][0] = f[1][1] = 0;
		for(int i = 2; i <= n + 1; i++) {
			chkmin(f[i][0], f[i - 1][0] + a[i - 2]);
			chkmin(f[i][0], f[i - 1][1]);
			chkmin(f[i][1], f[i - 1][0] + std::max(a[i - 2], a[i]));
			chkmin(f[i][1], f[i - 1][1] + a[i]);
		}
		assert(f[n + 1][0] == f[n + 1][1]);
		printf("%lld\n", f[n + 1][0]);
	}
	return 0;
}