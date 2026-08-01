#include <bits/stdc++.h>

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int Tid, n, m, Q;
int a[N], b[N];

namespace Solve {
	int a[N], b[N];
	int n, m;
	int solve() {
		memset(a, 0, sizeof(a)), memset(b, 0, sizeof(b));
		n = ::n, m = ::m;
		for(int i = 1; i <= n; i++) a[i] = ::a[i];
		for(int i = 1; i <= m; i++) b[i] = ::b[i];
		if(a[1] == b[1] || a[n] == b[m] || (a[1] < b[1]) != (a[n] < b[m])) return 0;
		if(a[1] > b[1]) {
			for(int i = 1; i <= std::max(n, m); i++) std::swap(a[i], b[i]);
			std::swap(n, m);
		}
		int mxa = *std::max_element(a + 1, a + n + 1), mnb = INF;
		for(int i = 1; i <= m; i++) {
			mnb = std::min(mnb, b[i]);
			if(b[i] > mxa)
		}
		return 0;
	}
}

int main() {
#ifndef DEBUG
	freopen("expand.in", "r", stdin);
	freopen("expand.out", "w", stdout);
#endif
	scanf("%d%d%d%d", &Tid, &n, &m, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
	putchar('0' + Solve::solve());
	while(Q--) {
		int kx, ky, x, y;
		scanf("%d%d", &kx, &ky);
		std::vector<std::pair<int, int>> vx, vy;
		while(kx--) scanf("%d%d", &x, &y), vx.push_back({x, a[x]}), a[x] = y;
		while(ky--) scanf("%d%d", &x, &y), vy.push_back({x, b[x]}), b[x] = y;
		putchar('0' + Solve::solve());
		for(auto p : vx) a[p.first] = p.second;
		for(auto p : vy) b[p.first] = p.second;
	}
	puts("");
	return 0;
} /*
1 4 4 0
0 3 2 0
3 5 3 2
*/