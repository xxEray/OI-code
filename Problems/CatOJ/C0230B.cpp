#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = 15 + 5;
const int MAXS = (1 << 15) + 5;

int n, m;
int a[N], b[N];
struct Edge { int u, v, w; } e[N * N];
bool operator<(Edge x, Edge y) { return x.w < y.w; }

int fa[N];
void init() { for(int i = 1; i <= n; i++) fa[i] = i; }
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

bool f[MAXS], ok[MAXS];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i++) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
		for(int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);
		std::sort(e + 1, e + m + 1);
		int U = (1 << n) - 1;
		for(int s = 0; s <= U; s++) f[s] = ok[s] = false;
		for(int s = 0; s <= U; s++) {
			init();
			int w = 0, c = 0;
			for(int i = 1; i <= m; i++)
				if((s >> (e[i].u - 1) & 1) && (s >> (e[i].v - 1) & 1) && find(e[i].u) != find(e[i].v))
					merge(e[i].u, e[i].v), w -= e[i].w, c++;
			for(int i = 1; i <= n; i++) if(s >> (i - 1) & 1) w += a[i] - b[i];
			ok[s] = (w >= 0 && c == __builtin_popcount(s) - 1);
			// if(w >= 0) printf("ok[%d] = 1\n", s);
		}
		f[0] = true;
		for(int s = 0; s <= U; s++)
			for(int t = (~s & U); t; t = (t - 1) & (~s & U))
				f[s | t] |= f[s] && ok[t];
		puts(f[U] ? "Yes" : "No");
	}
	return 0;
} /*
2
3 3
1 2 3
2 3 4
1 3 5
5 4
7 2
3 4
3 3
1 2 3
2 3 4
1 3 5
5 5
7 3
3 4
*/