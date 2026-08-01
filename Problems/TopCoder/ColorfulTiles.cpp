#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
#include <cassert>
using std::string;
using std::vector;

typedef long long LL;

const int N = 50 + 5;
const LL MOD = 1e9 + 7;

char a[N][N];
int n, m, K;

int char_map[300];

bool check(char ch[2][2]) {
	int cost = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cost += (a[i][j] != ch[i & 1][j & 1]);
	return cost <= K;
}

LL f[N][N * N], g[N][N * N][5];
LL solve(char ch[2][2]) {
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= K; j++)
			for(int t = 0; t <= 1; t++) {
				if(i <= 2 && t == 1) continue;
				int cost = 0;
				for(int k = 1; k <= m; k++) cost += (a[i][k] != ch[i & 1][(k & 1) ^ t]);
				if(j >= cost) (f[i][j] += f[i - 1][j - cost]) %= MOD;
			}
	LL ans = 0;
	for(int i = 0; i <= K; i++) (ans += f[n][i]) %= MOD;
	if(ans && 0) {
		puts("------------------------------");
		printf("solve [[%d, %d], [%d, %d]]  [", ch[1][1], ch[1][0], ch[0][1], ch[0][0]);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) printf("%d ", a[i][j]);
		printf("]\n");
		for(int i = 1; i <= n; i++) for(int j = 0; j <= K; j++) printf("%lld%c", f[i][j], " \n"[j == K]);
		printf("ans += %lld\n", ans);
	}
	return ans;
}

class ColorfulTiles {
public:
	int theCount(vector<string> room, int _K) {
		K = _K, n = room.size(), m = room[0].size();
		char_map['R'] = 1, char_map['G'] = 2, char_map['B'] = 3, char_map['Y'] = 4;
		LL ans = 0;
		char ch[2][2];
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = char_map[room[i - 1][j - 1]];
		if(n == 1 || m == 1) {
			if(n == 1) {
				for(int i = 1; i <= m; i++) for(int j = 1; j <= m; j++) if(i < j) std::swap(a[i][j], a[j][i]);
				std::swap(n, m);
			}
			for(int k = 1; k <= 4; k++) g[1][a[1][1] != k][k] = 1;
			for(int i = 2; i <= n; i++) for(int j = 0; j <= K; j++)
				for(int k1 = 1; k1 <= 4; k1++) for(int k2 = 1; k2 <= 4; k2++) if(k1 != k2)
					(g[i][j][k2] += g[i - 1][j - (k2 != a[i][1])][k1]) %= MOD;
			for(int j = 0; j <= K; j++) for(int k = 1; k <= 4; k++) (ans += g[n][j][k]) %= MOD;
			return ans;
		}
		for(int i = 1; i <= 4; i++)
			for(int j = 1; j <= 4; j++) if(j != i)
				for(int k = 1; k <= 4; k++) if(k != i && k != j)
					for(int t = 1; t <= 4; t++) if(t != i && t != j && t != k) {
						ch[0][0] = i, ch[0][1] = j, ch[1][0] = k, ch[1][1] = t;
						(ans += solve(ch)) %= MOD;
					}
		for(int i = 1; i <= std::max(n, m); i++) for(int j = 1; j <= std::max(n, m); j++) if(i < j) std::swap(a[i][j], a[j][i]);
		std::swap(n, m);
		for(int i = 1; i <= 4; i++)
			for(int j = 1; j <= 4; j++) if(j != i)
				for(int k = 1; k <= 4; k++) if(k != i && k != j)
					for(int t = 1; t <= 4; t++) if(t != i && t != j && t != k) {
						ch[0][0] = i, ch[0][1] = j, ch[1][0] = k, ch[1][1] = t;
						(ans += solve(ch)) %= MOD;
					}
		for(int i = 1; i <= 4; i++)
			for(int j = 1; j <= 4; j++) if(j != i)
				for(int k = 1; k <= 4; k++) if(k != i && k != j)
					for(int t = 1; t <= 4; t++) if(t != i && t != j && t != k) {
						ch[0][0] = i, ch[0][1] = j, ch[1][0] = k, ch[1][1] = t;
						(ans += MOD - check(ch)) %= MOD;
					}
		return ans;
	}
};