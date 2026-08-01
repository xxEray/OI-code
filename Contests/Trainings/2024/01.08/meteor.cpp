#include <bits/stdc++.h>

typedef long long LL;

const int N = 200 + 5;
const int M = 1e5 + 5;

int n, m;
std::array<int, 4> q[M];

std::bitset<N> g1[N][N], g2[N], g3;

int main() {
#ifndef DEBUG
	freopen("meteor.in", "r", stdin);
	freopen("meteor.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%d%d%d%d", &q[i][0], &q[i][1], &q[i][2], &q[i][3]), q[i][0]--, q[i][1]--, q[i][2]--, q[i][3]--;
	std::sort(q + 1, q + m + 1);
	int p = 1;
	LL ans = (LL)n * n * n * n;
	// LL ans = 0;
	for(int a = 0; a < n; a++) {
		for(int c = 0; c < n; c++) g2[c].reset();
		for(int b = 0; b < n; b++) {
			g3.reset();
			for(int c = 0; c < n; c++) {
				std::bitset<N> tmp = ~(g1[b][c] | g2[c] | g3), ret;
				auto set = [&](int i) { if(i < n) ret[i] = 1; };
				set(tmp._Find_first());
				int pp = p;
				while(p <= m && q[p][0] == a && q[p][1] == b && q[p][2] == c) {
					set(tmp._Find_next(q[p][3]));
					g1[b][c][q[p][3]] = 0;
					g2[c][q[p][3]] = 0;
					g3[q[p][3]] = 0;
					p++;
				}
				for(int i = pp; i < p; i++) ret[q[i][3]] = 0;
				ans -= ret.count();
				g1[b][c] |= ret;
				g2[c] |= ret;
				g3 |= ret;
			}
		}
	}
	// for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) for(int k = 0; k < n; k++) for(int t = 0; t < n; t++) printf("f[%d][%d][%d][%d] = %d\n", i, j, k, t, (int)f[i][j][k][t]);
	printf("%lld\n", ans - m);
	return 0;
} /*
37 0
*/