#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m, Q;
int a[N], qr[N];

namespace Solve1 {
	bool check() {
		if(n > 5000 || m > 5000 || Q > 5000) return false;
		for(int i = 1; i <= Q; i++) if(qr[i] > 5000) return false;
		return true;
	}
	LL out[N], b[N];
	LL calc(LL v) {
		LL ret = 0;
		for(int i = 1; i <= n; i++) if(b[i] > v) ret++, b[i] = v;
		return ret;
	}
	void main() {
		LL ret = 0;
		for(int i = 1, j = 1; i <= 20; i++) {
			for(int k = 1; k <= n; k++) b[k] += k;
			ret += calc(a[j]);
			out[i] = ret;
			j++;
			if(j > m) j = 1;
		}
		for(int i = 1; i <= Q; i++) printf("%lld\n", out[qr[i]]);
	}
}

int main() {
#ifndef DEBUG
	freopen("memory.in", "r", stdin);
	freopen("memory.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= m; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= Q; i++) scanf("%d", &qr[i]);
	if(Solve1::check()) Solve1::main();
	return 0;
} /*
3 2 5
3 2
2
3
4
5
6
*/
