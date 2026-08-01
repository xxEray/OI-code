#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N], ek;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }

int n;
int t[N], bel[N], out[N];

void dfs(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(!t[v]) t[v] = 3 - t[u], dfs(v);
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		ek = 1;
		for(int i = 1; i <= n; i++) head[i] = t[i] = 0;
		for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
		t[1] = 1, dfs(1);
		// for(int i = 1; i <= n; i++) printf("t[%d] = %d\n", i, t[i]);
		int cnt1 = 0, cnt2 = 0;
		for(int i = 1; i <= n; i++) t[i] == 1 ? cnt1++ : cnt2++;
		if(cnt1 > cnt2) {
			std::swap(cnt1, cnt2);
			for(int i = 1; i <= n; i++) t[i] = 3 - t[i];
		}
		for(int i = 1; i <= n; i++) {
			int highbit = -1;
			for(int j = 31; j >= 0; j--) if(i >> j & 1) { highbit = j; break; }
			if(cnt1 >> highbit & 1) bel[i] = 1;
			else bel[i] = 2;
		}
		for(int i = 1, c1 = 1, c2 = 1; i <= n; i++)
			if(t[i] == 1) {
				while(bel[c1] == 2) c1++;
				out[i] = c1++;
			} else {
				while(bel[c2] == 1) c2++;
				out[i] = c2++;
			}
		for(int i = 1; i <= n; i++) printf("%d ", out[i]);
		puts("");
	}
	return 0;
} /*
1
15
2 15
1 9
12 15
4 8
13 11
1 2
15 14
4 5
1 6
10 7
3 14
11 5
10 14
10 11
*/