#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int n, Q;
int p[N], dep[N];

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? (dep[x] < dep[y] ? fa[y] = x : fa[x] = y) : 0; }

int main() {
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) scanf("%d", &p[i]);
	for(int i = 1; i <= n; i++) dep[i] = dep[p[i]] + 1;
	for(int i = 1; i <= n; i++) fa[i] = i;
	scanf("%d", &Q);
	while(Q--) {
		int type;
		scanf("%d", &type);
		if(type == 1) {
			int u, v;
			scanf("%d%d", &u, &v);
			while((u = find(u)) != find(v)) merge(u, p[u]);
		} else {
			int u;
			scanf("%d", &u);
			printf("%d\n", find(u));
		}
	}
	return 0;
}