#include <bits/stdc++.h>

typedef long long LL;

const LL MOD = 998244353;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m, s, t, L, R;

namespace Subtask1 {
	const int N = (1 << 10) + 5;
	const int M = 2000 + 5;
	int mod;
	struct State { LL cnt, sum; } f[M][N];
	State operator+(const State &x, int y) { return (State){x.cnt, (x.sum + x.cnt * y) % MOD}; }
	State operator+(const State &x, const State &y) { return (State){(x.cnt + y.cnt) % MOD, (x.sum + y.sum) % MOD}; }
	void main() {
		mod = (1 << m) - 1;
		for(int j = 0; j <= n; j++) for(int i = 0; i < mod; i++) f[j][i] = {0, 0};
		f[0][s] = {1, (L <= s && s <= R)};
		for(int j = 1; j <= n; j++) for(int i = 0; i < mod; i++) {
			int i_ = (i << 1) % mod;
			f[j][i_] = f[j][i_] + (f[j - 1][i] + (L <= i_ && i_ <= R));
			i_ = (i << 1 | 1) % mod;
			f[j][i_] = f[j][i_] + (f[j - 1][i] + (L <= i_ && i_ <= R));
		}
		printf("%lld\n", f[n][t].sum);
	}
}

int main() {
#ifndef DEBUG
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d%d%d%d", &n, &m, &s, &t, &L, &R);
		Subtask1::main();
	}
	return 0;
}