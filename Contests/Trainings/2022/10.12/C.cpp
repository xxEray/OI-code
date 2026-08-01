#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#include <memory>

const int N = 150 + 5;
const int M = 10 + 3;
const int MAXS = 6e4;
const int INF = 0x3f3f3f3f;

const int pow3[] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147};

int n, m, K;
int a[N][M];

#define at(v, k) ((v) / pow3[(k)] % 3)

std::vector<std::pair<int, int>> trans[MAXS];

bool ok[N][MAXS];

void dfs(int s, int t, int bit, int type, int cost) {
	if(bit == m) {
		if(!type) trans[s].push_back({t, cost});
		return;
	}
	if(at(s, bit) == 0) {
		if(type) dfs(s, t + (type == 1 ? 2 : 1) * pow3[bit], bit + 1, type == 2 ? 0 : type - 1, cost);
		else {
			dfs(s, t, bit + 1, 0, cost);
			dfs(s, t + 2 * pow3[bit], bit + 1, 1, cost + 1); // 1 -> 0
			dfs(s, t + pow3[bit], bit + 1, 3, cost + 1); // 3 -> 2 -> 0
		}
	} else {
		if(type) return;
		else dfs(s, t + (at(s, bit) - 1) * pow3[bit], bit + 1, 0, cost);
	}
}

char tmp1[100], tmp2[100];
const char *tri(char *str, int x) {
	int c = 0;
	for(int i = 0; i < m; i++) str[c++] = at(x, i) + '0';
	str[c] = 0;
	return str;
}

int f[2][MAXS];

int main() {
#ifndef DEBUG
	freopen("candy.in", "r", stdin);
	freopen("candy.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &m, &K);
		for(int i = 0; i < pow3[m]; i++) trans[i].clear();
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = 1;
		while(K--) { int x, y; scanf("%d%d", &x, &y); a[x][y] = 0; }
		for(int s = 0; s < pow3[m]; s++) dfs(s, 0, 0, 0, 0);
		// for(int s = 0; s < pow3[m]; s++) for(auto [t, w] : trans[s]) printf("%s -> %s (w=%d) [%d -> %d]\n", tri(tmp1, s), tri(tmp2, t), w, s, t);
		for(int i = 0; i <= 1; i++) for(int s = 0; s < pow3[m]; s++) f[i][s] = -INF;
		for(int i = 0; i <= n; i++) {
			int mx[15];
			for(int j = 0; j < m; j++)
				if(!a[i][j + 1]) mx[j] = 0;
				else if(i <= n - 1 && !a[i + 1][j + 1]) mx[j] = 0;
				else if(i <= n - 2 && !a[i + 2][j + 1]) mx[j] = 1;
				else mx[j] = 2;
			int arr[15] = {};
			int p = 0, s = 0;
			while(p >= 0) {
				if(p == m) { ok[i][s] = true; p--; continue; }
				if(arr[p] == mx[p]) { p--; continue; }
				arr[p]++, s += -at(s, p) + arr[p] * pow3[p], arr[++p] = -1;
			}
		}
		puts("ok");
		f[0][0] = 0;
		for(int i = 0; i < n; i++) {
			// for(int s = 0; s < pow3[m]; s++) if(f[i & 1][s] >= 0) printf("f[%d][%s] = %d\n", i, tri(tmp1, s), f[i & 1][s]);
			for(int s = 0; s < pow3[m]; s++) f[(i & 1) ^ 1][s] = -INF;
			for(int s = 0; s < pow3[m]; s++) {
				if(!ok[i][s]) continue;
				for(auto p : trans[s]) {
					int t = p.first, w = p.second;
					if(!ok[i + 1][t]) continue;
					f[(i & 1) ^ 1][t] = std::max(f[(i & 1) ^ 1][t], f[i & 1][s] + w);
				}
			}
		}
		// for(int s = 0; s < pow3[m]; s++) if(f[n & 1][s] >= 0) printf("f[%d][%s] = %d\n", n, tri(tmp1, s), f[n & 1][s]);
		printf("%d\n", f[n & 1][0]);
	}
	return 0;
}