#include <bits/stdc++.h>

const int N = 5000 + 5;

int n;
int a[N];

int mex[N][N];
int mx[2 * N];
bool vis[N];

bool f[N][2 * N];
std::vector<int> cf[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j <= n; j++) vis[j] = false;
			int p = 0;
			for(int j = i; j <= n; j++) {
				vis[a[j]] = true;
				while(vis[p]) p++;
				mex[i][j] = p;
			}
		}
		for(int i = 0; i <= 8191; i++) mx[i] = 0;
		for(int i = 0; i <= n; i++) for(int j = 0; j <= 8191; j++) f[i][j] = false;
		f[0][0] = true, cf[0].push_back(0);
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j <= 8191; j++) f[i][j] = f[i - 1][j];
			for(int j = 1; j <= i; j++) while(mx[mex[j][i]] < j) {
				for(int k : cf[mx[mex[j][i]]]) f[i][k ^ mex[j][i]] |= f[mx[mex[j][i]]][k];
				mx[mex[j][i]]++;
				// printf("%d: mx[%d] -> %d\n", i, mex[j][i], mx[mex[j][i]]);
			}
			for(int j = 0; j <= 8191; j++) if(f[i - 1][j] ^ f[i][j]) cf[i].push_back(j);
			// for(int j = 0; j <= 8191; j++) if(f[i][j]) printf("f[%d][%d] = %d\n", i, j, f[i][j]);
		}
		int ans = 0;
		for(int j = 0; j <= 8191; j++) if(f[n][j]) ans = std::max(ans, j);
		printf("%d\n", ans);
	}
	return 0;
} /*
1
2-
1 0
*/