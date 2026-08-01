#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

const int N = 100 + 5;
const int K = 100 + 5;
const int MOD = 998244353;

int a[K], nxtcnt[K];
std::vector<int> nxt[K][N];
int n;

namespace SolveK2N10 { // k = 2, n <= 10
	bool vis[N];
	int to[N];
	int ans = 0;
	int calc() {
		int cnt = 0;
		// printf("to: ");
		// for(int i = 1; i <= a[1]; i++) printf("%d ", to[i]);
		// puts("");
		for(int i = 1; i <= a[1]; i++)
			for(int j = i + 1; j <= a[1]; j++)
				if(to[i] > to[j]) cnt++;
		return cnt & 1 ? MOD - 1 : 1;
	}
	void dfs(int x) {
		if(x > n) { (ans += calc()) %= MOD; return; }
		for(int y : nxt[1][x])
			if(!vis[y]) {
				to[x] = y, vis[y] = true;
				dfs(x + 1);
				vis[y] = false;
			}
	}
	void main() {
		for(int i = 1; i <= n; i++) vis[i] = false;
		dfs(1);
		printf("%d\n", (ans + MOD) % MOD);
	}
}

namespace SolveK10N10AB { // k = 10, n <= 10, both A and B
	bool reach[K][N];
	void main() {
		for(int i = 1; i <= a[1]; i++) reach[1][i] = true;
		for(int i = 1; i < n; i++)
			for(int j = 1; j <= a[i]; j++)
				for(int k : nxt[i][j])
					reach[i + 1][k] |= reach[i][j];
		int cnt = 0;
		for(int i = 1; i <= a[n]; i++) cnt += reach[n][i];
		printf("%d\n", cnt >= a[1] ? 1 : 0);
	}
}

int main() {
// #ifndef DEBUG
	freopen("xpath.in", "r", stdin);
	freopen("xpath.out", "w", stdout);
// #endif
	int T;
	scanf("%d", &T);
	while(T--) {
		int maxcnt = 0;
		for(int i = 0; i <= 10; i++)
			for(int j = 0; j <= 100; j++)
				nxt[i][j].clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i < n; i++) scanf("%d", &nxtcnt[i]), maxcnt = std::max(maxcnt, nxtcnt[i]);
		for(int i = 1; i < n; i++)
			for(int j = 1; j <= nxtcnt[i]; j++)
				{ int u, v; scanf("%d%d", &u, &v); nxt[i][u].push_back(v); }
		if(n == 2 && maxcnt <= 10) SolveK2N10::main();
		else SolveK10N10AB::main();
	} 
	return 0;
} /*
1
2
2 3
5
1 1
1 2
2 1
2 2
2 3
*/