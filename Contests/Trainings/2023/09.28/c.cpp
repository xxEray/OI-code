#include <bits/stdc++.h>

const int N = 16 + 3;
const int MAXS = (1 << 16) + 5;
const int INF = 0x3f3f3f3f;

int n, m;

int pre[N], w[N];
int f[N][MAXS], last[N][MAXS];

int out[N];
void get_answer(int i, int s) {
	if(!i) { /* assert(s == 0); */ return; }
	int t = last[i][s];
	for(int j = 1; j <= n; j++) if(t >> (j - 1) & 1) out[j] = i;
	get_answer(i - 1, s ^ t);
}

int main() {
#ifndef DEBUG
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) pre[i] = w[i] = 0;
		for(int i = 1; i <= m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			pre[v] |= (1 << (u - 1));
			w[u]--, w[v]++;
		}
		int U = (1 << n) - 1;
		for(int i = 0; i <= n; i++) for(int j = 0; j <= U; j++) f[i][j] = INF, last[i][j] = 0;
		f[0][0] = 0;
		for(int i = 0; i < n; i++)
			for(int s = 0; s <= U; s++)
				for(int t = ~s & U; t; t = (t - 1) & (~s & U)) {
					bool flag = true;
					int cost = 0;
					for(int j = 1; j <= n; j++) if(t >> (j - 1) & 1) flag &= ((s & pre[j]) == pre[j]), cost += w[j] * (i + 1);
					if(flag && f[i][s] + cost < f[i + 1][s | t]) {
						f[i + 1][s | t] = f[i][s] + cost;
						last[i + 1][s | t] = t;
					}
				}
		int id = 0;
		for(int i = 1; i <= n; i++) if(f[i][U] < f[id][U]) id = i;
		if(f[id][U] == INF) puts("NIE");
		else {
			printf("%d\n", f[id][U]);
			get_answer(id, U);
			for(int i = 1; i <= n; i++) printf("%d ", out[i]);
			puts("");
		}
	}
	return 0;
}