#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = 1e5 + 5;

int n, Q;
struct Edge { int to, nxt, w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

int fa[N], dfn[N], out[N], which[N], dep[N];
int sum[N];
void dfs(int u) {
	static int ts = 0;
	dfn[u] = ++ts;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u, sum[v] = sum[u] ^ edge[i].w, which[v] = (u == 1 ? v : which[u]);
		dep[v] = dep[u] + 1;
		dfs(v);
	}
	out[u] = ts;
}

int cnt[N], tmp[N];

int triec;
int trie[N * 35][2];
int nw() { triec++; trie[triec][0] = trie[triec][1] = 0; return triec; }
bool ancestor(int x, int y) { return dfn[x] <= dfn[y] && dfn[y] <= out[x]; }

int main() {
#ifndef DEBUG
	freopen("nim.in", "r", stdin);
	freopen("nim.out", "w", stdout);
#endif
	scanf("%d%d", &n, &Q);
	for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); u++, v++; add_edge(u, v, w), add_edge(v, u, w); }
	dfs(1);
	int flag = true, mx = 0;
	for(int u = 1; u <= n; u++) {
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(v > u) continue;
			if(fa[u] == v) {
				cnt[v]++;
				if((v != 1 && cnt[v] > 1) || (v == 1 && cnt[v] > 2)) flag = false;
			} else {
				cnt[u]++;
				if((u != 1 && cnt[u] > 1) || (u == 1 && cnt[u] > 2)) flag = false;
			}
		}
		if(!flag) break;
		mx = u;
	}
	// printf("available: [0, %d]\n", mx);
	while(Q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		int left = 0, right = mx;
		while(left < right) {
			int mid = (left + right + 1) >> 1;
			assert(mid > 1);
			// printf("check %d\n", mid);
			int x = 1, y = 1;
			for(int i = 1; i <= n; i++) tmp[i] = 0;
			for(int i = 1; i <= mid; i++) if(!tmp[which[i]] || dep[tmp[which[i]]] < dep[i]) tmp[which[i]] = i;
			for(int i = 1; i <= n; i++) if(tmp[i]) (x == 1 ? x : y) = tmp[i];
			// printf("x = %d, y = %d\n", x, y);
			triec = 0;
			int rt = nw();
			for(int i = 1; i <= n; i++) if(ancestor(x, i) && which[i] != which[y]) {
				int now = rt, v = sum[i];
				for(int j = 30; j >= 0; j--) {
					if(!trie[now][v >> j & 1]) trie[now][v >> j & 1] = nw();
					now = trie[now][v >> j & 1];
				}
			}
			flag = false;
			for(int i = 1; i <= n; i++) if(ancestor(y, i) && which[i] != which[x]) {
				int now = rt, v = sum[i];
				int j;
				for(j = 30; j >= 0 && (l >> j & 1) == (r >> j & 1); j--) now = trie[now][(l >> j & 1) ^ (v >> j & 1)];
				if(!now) continue;
				if(j == -1) { flag = true; break; }
				int nowl = trie[now][(v >> j & 1)], nowr = trie[now][1 ^ (v >> j & 1)];
				int clonej = j;
				bool flag2 = true;
				for(j = clonej - 1; j >= 0; j--)
					if((l >> j & 1) && !trie[nowl][1 ^ (v >> j & 1)]) flag2 = false;
					else if(!(l >> j & 1) && trie[nowl][1 ^ (v >> j & 1)]) break;
					else nowl = trie[nowl][(l >> j & 1) ^ (v >> j & 1)];
				if(nowl && flag2) { flag = true; break; }
				flag2 = true;
				for(j = clonej - 1; j >= 0; j--)
					if(!(r >> j & 1) && !trie[nowr][v >> j & 1]) flag2 = false;
					else if((r >> j & 1) && trie[nowr][v >> j & 1]) break;
					else nowr = trie[nowr][(r >> j & 1) ^ (v >> j & 1)];
				if(nowr && flag2) { flag = true; break; }
			}
			if(flag) left = mid;
			else right = mid - 1;
		}
		printf("%d\n", left);
	}
	return 0;
} /*
5 5
2 1 0
4 2 1
1 0 1
3 1 2
0 4
1 4
2 6
0 7
1 2
*/