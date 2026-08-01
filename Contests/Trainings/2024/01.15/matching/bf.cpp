#include <bits/stdc++.h>

const int N = 20 + 5;

int n, m;
int id[N][N];
int e[N][N];

int p[N];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= 2 * n; i++) for(int j = 1; j <= 2 * n; j++) e[i][j] = -1, id[i][j] = 0;
		for(int i = 1; i <= m; i++) {
			int u, v, t;
			scanf("%d%d%d", &u, &v, &t);
			e[u][v] = t;
			id[u][v] = i;
		}
		for(int i = 1; i <= n; i++) p[i] = i;
		bool ok = false;
		do {
			bool flag = true;
			int cnt = 0;
			for(int i = 1; i <= n; i++) flag &= (e[i][p[i] + n] != -1), cnt += e[i][p[i] + n];
			if(flag && (~cnt & 1)) { ok = true; break; }
		} while(std::next_permutation(p + 1, p + n + 1));
		if(ok) {
			for(int i = 1; i <= n; i++) printf("%d ", id[i][p[i] + n]);
			puts("");
		} else puts("-1");
	}
	return 0;
}