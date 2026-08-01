#include <bits/stdc++.h>

namespace FIO {
	const int D = (1 << 23) + 1;
	char in[D], *I = in + D, *Iend = in + D;
	char gc() { return (I == in + D ? Iend = in + fread(I = in, 1, D, stdin) : 0), I == Iend ? EOF : *I++; }
	template<typename T>
	void read(T &x) {
		char ch = gc();
		while(ch < '0' || ch > '9') ch = gc();
		for(x = 0; '0' <= ch && ch <= '9'; ch = gc()) x = x * 10 + (ch - '0');
	}
}
using FIO::read;

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 998244353;

int n;
int a[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

int pre[N], cnt0[N];
std::map<int, std::vector<int>> cnt;

int main() {
#ifndef DEBUG
	freopen("dust.in", "r", stdin);
	freopen("dust.out", "w", stdout);
#endif
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]);
	for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] ^ a[i];
	for(int i = 1; i <= n; i++) {
		cnt0[i] = cnt0[i - 1] + (pre[i] == 0);
		if(pre[i]) cnt[pre[i]].emplace_back(i);
	}
	// printf("pre: "); for(int i = 1; i <= n; i++) printf("%d ", pre[i]); puts("");
	// printf("cnt0: "); for(int i = 1; i <= n; i++) printf("%d ", cnt0[i]); puts("");
	LL ans = 0;
	if(pre[n] == 0) (ans += qpow(2, cnt0[n] - 1) % MOD) %= MOD;
	for(auto &&[xor_sum, vct] : cnt) if(pre[n] == 0 || pre[n] == xor_sum) {
		LL f, sumf = 0, sumwf = 0;
		// printf("xor_sum = %d:\n", xor_sum);
		int last = 0;
		for(int i : vct) {
			(sumwf += sumf * (cnt0[i] - last)) %= MOD, last = cnt0[i];
			f = sumwf + 1;
			(sumf += f) %= MOD;
			// printf("  f[%d]=%lld\n", i, f);
		}
		(ans += f) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
} /*
5
1 1 4 2 7
*/
