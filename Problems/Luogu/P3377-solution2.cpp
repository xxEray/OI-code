#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, m;

struct HeapNode { int ls, rs, dep, id, val; } t[N];
int merge(int x, int y) {
	if(!x || !y) return x ^ y;
	if(t[x].val > t[y].val || (t[x].val == t[y].val && t[x].id > t[y].id)) std::swap(x, y);
	t[x].rs = merge(t[x].rs, y);
	if(t[t[x].ls].dep < t[t[x].rs].dep) std::swap(t[x].ls, t[x].rs);
	t[x].dep = t[t[x].rs].dep + 1;
	return x;
}

bool erased[N];
int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge_dsu(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[y] = x : 0; }

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &t[i].val), t[i].dep = 1, t[i].id = i;
	for(int i = 1; i <= n; i++) fa[i] = i;
	while(m--) {
		int type, x, y;
		scanf("%d", &type);
		if(type == 1) {
			scanf("%d%d", &x, &y);
			if(erased[x] || erased[y]) continue;
			x = find(x), y = find(y);
			if(x == y) continue;
			int z = merge(x, y);
			if(z == x) merge_dsu(x, y);
			else merge_dsu(y, x);
		} else {
			scanf("%d", &x);
			if(erased[x]) { puts("-1"); continue; }
			x = find(x);
			printf("%d\n", t[x].val);
			erased[x] = true;
			int z = merge(t[x].ls, t[x].rs);
			fa[x] = fa[z] = z;
		}
		// for(int i = 1; i <= n; i++) printf("%d: ls=%d, rs=%d, id=%d, dep=%d, rt=%d\n", i, t[i].ls, t[i].rs, t[i].id, t[i].dep, find(i));
	}
	return 0;
}