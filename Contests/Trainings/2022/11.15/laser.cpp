#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, m, K;
int x[N], y[N], z[N];

std::set<std::pair<int, int>> r[N], c[N];

int to[N], near[N][4];

int tmp[N];
void discrete() {
	int cn = 0;
	for(int i = 1; i <= K; i++) tmp[++cn] = x[i];
	std::sort(tmp + 1, tmp + cn + 1);
	cn = std::unique(tmp + 1, tmp + cn + 1) - tmp - 1;
	for(int i = 1; i <= K; i++) x[i] = std::lower_bound(tmp + 1, tmp + cn + 1, x[i]) - tmp;
	cn = 0;
	for(int i = 1; i <= K; i++) tmp[++cn] = y[i];
	std::sort(tmp + 1, tmp + cn + 1);
	cn = std::unique(tmp + 1, tmp + cn + 1) - tmp - 1;
	for(int i = 1; i <= K; i++) y[i] = std::lower_bound(tmp + 1, tmp + cn + 1, y[i]) - tmp;
}

int main() {
#ifndef DEBUG
	freopen("laser.in", "r", stdin);
	freopen("laser.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &m, &K);
		for(int i = 1; i <= K; i++) {
			char s[3];
			scanf("%d%d%s", &x[i], &y[i], s);
			if(s[0] == 'L' || s[0] == 'R') z[i] = (s[0] == 'L' ? 3 : 1);
			else z[i] = (s[0] == 'U' ? 0 : 2);
		}
		discrete();
		for(int i = 1; i <= K; i++) r[i].clear(), c[i].clear();
		for(int i = 1; i <= K; i++) {
			r[x[i]].insert({y[i], i});
			c[y[i]].insert({x[i], i});
		}
		for(int i = 1; i <= K; i++) {
			std::set<std::pair<int, int>>::iterator it;
			it = c[y[i]].lower_bound({x[i], 0});
			near[i][0] = (it == c[y[i]].begin() ? 0 : std::prev(it)->second);
			it = r[x[i]].upper_bound({y[i], K});
			near[i][1] = (it == r[x[i]].end() ? 0 : it->second);
			it = c[y[i]].upper_bound({x[i], K});
			near[i][2] = (it == c[y[i]].end() ? 0 : it->second);
			it = r[x[i]].lower_bound({y[i], 0});
			near[i][3] = (it == r[x[i]].begin() ? 0 : std::prev(it)->second);
			to[i] = near[i][z[i]];
		}
		// for(int i = 1; i <= K; i++) printf("to[%d] = %d\n", i, to[i]);
		int p = 0, q = 0, cnt = 0;
		for(int i = 1; i <= K; i++) if(to[to[i]] == i && i < to[i]) p = i, q = to[i], cnt++;
		if(cnt == 0) puts("Yes");
		else if(cnt > 1) puts("No");
		else {
			bool flag = false;
			for(int j = 0; j < 4; j++) flag |= (to[near[p][j]] != p || to[near[q][j]] != q);
			puts(flag ? "Yes" : "No");
		}
	}
	return 0;
}
