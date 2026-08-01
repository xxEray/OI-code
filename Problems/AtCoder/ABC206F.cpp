#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = 100 + 5;

int l[N], r[N];
int n;

int sg[N][N], cnt[N * N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		int mx = 0;
		for(int i = 1; i <= n; i++) scanf("%d%d", &l[i], &r[i]), r[i]--, mx = std::max(mx, r[i]);
		for(int len = 1; len <= mx; len++) for(int i = 1; i + len - 1 <= mx; i++) {
			int j = i + len - 1;
			for(int k = 1; k <= n; k++) if(i <= l[k] && r[k] <= j) cnt[sg[i][l[k] - 1] ^ sg[r[k] + 1][j]]++;
			int mex = 0;
			while(cnt[mex]) mex++;
			sg[i][j] = mex;
			for(int k = 1; k <= n; k++) if(i <= l[k] && r[k] <= j) cnt[sg[i][l[k] - 1] ^ sg[r[k] + 1][j]]--;
		}
		// for(int i = 1; i <= mx; i++) for(int j = i; j <= mx; j++) printf("SG(%d, %d) = %d\n", i, j, sg[i][j]);
		puts(sg[1][mx] == 0 ? "Bob" : "Alice");
	}
	return 0;
} /*
1
2
1 2
3 4
*/