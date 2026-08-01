// train
#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 50 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;

int gl, gr, sl, sr;
LL dis[N][N];
LL f[N][N][N][2][2];
LL fast[N], slow[N];
bool cangold[N], cansilver[N], canbronze[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) fast[i] = LLINF, slow[i] = -LLINF;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = (i == j ? 0 : LLINF);
	for(int i = 1; i <= m; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); dis[u][v] = dis[v][u] = std::min(dis[u][v], w); }
	scanf("%d%d%d%d", &gl, &gr, &sl, &sr);
	for(int k = 1; k <= n; k++)
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = dis[i][j] * n + i;
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(i != j) printf("dis[%d][%d] = %lld\n", i, j, dis[i][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(i != j) fast[i] = std::min(fast[i], dis[i][j]), slow[i] = std::max(slow[i], dis[i][j]);
	LL ans = 0;
	for(int oi = 1; oi <= n; oi++) for(int oj = 1; oj <= n; oj++) {
		int goldline = fast[oi], bronzeline = slow[oj];
		if(goldline > bronzeline) continue;
		for(int i = 1; i <= n; i++) cangold[i] = (fast[i] <= goldline), canbronze[i] = (slow[i] >= bronzeline), cansilver[i] = false;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(i != j) cansilver[i] |= (goldline < dis[i][j] && dis[i][j] < bronzeline);
		for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) for(int k = 0; k <= n; k++) f[i][j][k][0][0] = f[i][j][k][0][1] = f[i][j][k][1][0] = f[i][j][k][1][1] = 0;
		f[0][0][0][0][0] = 1;
		for(int i = 1; i <= n; i++) for(int j = 0; j <= gr; j++) for(int k = 0; k <= sr; k++) {
			if(j && cangold[i]) {
				if(fast[i] == goldline){
					f[i][j][k][1][0] += f[i - 1][j - 1][k][0][0] + f[i - 1][j - 1][k][1][0];
					f[i][j][k][1][1] += f[i - 1][j - 1][k][0][1] + f[i - 1][j - 1][k][1][1];
				} else {
					f[i][j][k][0][0] += f[i - 1][j - 1][k][0][0], f[i][j][k][1][0] += f[i - 1][j - 1][k][1][0];
					f[i][j][k][0][1] += f[i - 1][j - 1][k][0][1], f[i][j][k][1][1] += f[i - 1][j - 1][k][1][1];
				}
			}
			if(k && cansilver[i]) {
				f[i][j][k][0][0] += f[i - 1][j][k - 1][0][0];
				f[i][j][k][0][1] += f[i - 1][j][k - 1][0][1];
				f[i][j][k][1][0] += f[i - 1][j][k - 1][1][0];
				f[i][j][k][1][1] += f[i - 1][j][k - 1][1][1];
			}
			if(canbronze[i]) {
				if(slow[i] == bronzeline) {
					f[i][j][k][0][1] += f[i - 1][j][k][0][0] += f[i - 1][j][k][0][1];
					f[i][j][k][1][1] += f[i - 1][j][k][1][0] += f[i - 1][j][k][1][1];
				} else {
					f[i][j][k][0][0] += f[i - 1][j][k][0][0], f[i][j][k][0][1] += f[i - 1][j][k][0][1];
					f[i][j][k][1][0] += f[i - 1][j][k][1][0], f[i][j][k][1][1] += f[i - 1][j][k][1][1];
				}
			}
		}
		for(int i = gl; i <= gr; i++) for(int j = sl; j <= sr; j++) ans += f[n][i][j][1][1];
	}
	printf("%lld\n", ans);
	return 0;
} /*
45 44
1 2 849
1 3 447
3 4 977
1 5 731
3 6 164
1 7 2
5 8 838
3 9 21
4 10 923
4 11 889
2 12 913
8 13 387
2 14 953
11 15 210
13 16 744
11 17 16
4 18 620
1 19 462
19 20 38
7 21 68
17 22 419
22 23 538
20 24 165
8 25 253
12 26 668
3 27 409
26 28 717
9 29 232
3 30 861
25 31 788
26 32 613
13 33 551
31 34 953
14 35 508
26 36 550
26 37 617
4 38 744
34 39 204
39 40 573
33 41 671
23 42 994
2 43 513
18 44 384
8 45 346
26 29 9 12

*/